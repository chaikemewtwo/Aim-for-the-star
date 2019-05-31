#include "Player.h"
#include "PlayerState/PlayerWaitState/PlayerWaitState.h"
#include "PlayerState/PlayerSwimState/PlayerSwimState.h"
#include "PlayerState/PlayerStandingWaitState/PlayerStandingWaitState.h"
#include "PlayerState/PlayerDeathState/PlayerDeathState.h"
#include <cmath>
#include <time.h>
#include "../Map/MapChip/MapChip.h"
#include "../Lib/Sound/DirectSound.h"



Player::Player(ID id) :m_state(PlayerWaitState::GetInstance()) {
	Keybord& kb = Keybord::getInterface();

	// 半径
	m_radius = 64.f;
	// 当たり位置の頂点を画像の中心にずらす
	m_hit_vertex_shift.x = 64.f;
	m_hit_vertex_shift.y = 64.f;

	// 生存フラグ
	m_is_alive = true;

	// 移動速度
	m_speed = 3.f;

	// 傾き
	m_character_angle = 0.f;

	// アニメーション番号
	m_animation_num = 0;

	// 移動量
	m_move.x = 0.f;
	m_move.y = 0.f;

	m_proto_move.x = 0.f;
	m_proto_move.y = 0.f;

	// 状態推移初期化
	m_state->Init(this);

	// スタミナ
	m_stamina = MAX_STAMINA;

	// 描画フラグ
	m_draw_enable = true;

	// ソート
	m_sort_object = SortObject::PLAYER;

	// 自機1（ヒくん、オレンジの方）
	if (id == STAR_1) {
		// 位置
		m_pos.x = STAR_1_FIRST_POS_X;
		m_pos.y = STAR_1_FIRST_POS_Y - 200;

		// 操作
		imput_button_name[LEFT_KEY][256] = 'A';
		imput_button_name[RIGHT_KEY][256] = 'D';
		imput_button_name[SWIM_KEY][256] = 'W';
		imput_button_name[PULL_ROPE_KEY][256] = 'Q';
	
		// 画像
		star_texture_name[WAIT_TEXTURE] = "Resource/Texture/Player/de_wait.png";
		star_texture_name[STANDING_WAIT_TEXTURE] = "Resource/Texture/Player/de_standing_wait.png";
		star_texture_name[SWIM_TEXTURE] = "Resource/Texture/Player/de_swim.png";
		//star_texture_name[GRAB_TEXTURE] = "Resource/de_swim.png";
		//star_texture_name[PULL_ROPE_TEXTURE] = "Resource/de_swim.png";
		star_texture_name[DEATH_TEXTURE] = "Resource/Texture/Player/de_die.png";
	}
	// 自機2（デちゃん、ピンクの方）
	else if (id == STAR_2) {
		// 位置
		m_pos.x = STAR_2_FIRST_POS_X;
		m_pos.y = STAR_2_FIRST_POS_Y - 200;

		// 操作
		imput_button_name[LEFT_KEY][256] = VK_LEFT;
		imput_button_name[RIGHT_KEY][256] = VK_RIGHT;
		imput_button_name[SWIM_KEY][256] = VK_UP;
		imput_button_name[PULL_ROPE_KEY][256] = 'M';

		// 画像
		star_texture_name[WAIT_TEXTURE] = "Resource/Texture/Player/hi_wait.png";
		star_texture_name[STANDING_WAIT_TEXTURE] = "Resource/Texture/Player/hi_standing_wait.png";
		star_texture_name[SWIM_TEXTURE] = "Resource/Texture/Player/hi_swim.png";
		//star_texture_name[GRAB_TEXTURE] = "Resource/de_swim.png";
		//star_texture_name[PULL_ROPE_TEXTURE] = "Resource/de_swim.png";
		star_texture_name[DEATH_TEXTURE] = "Resource/Texture/Player/hi_die.png";
	}
	// WaitState初回のみ画像の初期化をしてやる（画像の初期化がWaitStateが生成されるタイミングより遅いため）
	// HACK:もっといい書き方ありそう
	m_player_texture = star_texture_name[WAIT_TEXTURE];
}


void Player::Update() {

	// 移動量を初期化（マップの当たり判定で必要）
	m_move.x = 0.f;
	m_move.y = 0.f;

	// スタミナ自動回復
	if (m_stamina < MAX_STAMINA && m_is_alive == true && swim_enable == false){
		++m_stamina;
	}
	if(m_is_alive == true && m_stamina <= 0){
		DisableIsAlive();
	}

	// ステート更新
	// 内部の処理は各ステート内で管理しています
	m_state->Update(this);

	m_pos += m_move;
}


void Player::Draw() {
	// 第7、8引数が0.5fずつで中心座標から描画	
	// 被弾状態は描画する、しないを切り替えて表現する
	if (m_draw_enable == true) {
		Texture::Draw2D(
			m_player_texture.c_str(),
			m_pos.x,
			m_pos.y,
			TEXTURE_SIZE_X,
			TEXTURE_SIZE_Y,
			m_character_angle,
			0.5f,
			0.5f,
			true,
			TEXTURE_PARTITION_X_NUMBER,
			TEXTURE_PARTITION_Y_NUMBER,
			m_animation_num
		);
	}
}


void Player::AddGravity() {
	// 常時下方向へ負荷がかかる
	m_move.y -= GRAVITY;
}


void Player::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (m_character_angle <= MAX_ANGLE && m_character_angle >= -MAX_ANGLE) {
		m_character_angle += is_move_right ? ANGLE_ADD : -ANGLE_ADD;
	}
	// 角度変更範囲設定
	// 左
	else if (m_character_angle >= MAX_ANGLE) {
		m_character_angle = MAX_ANGLE;
	}
	// 右
	else if (m_character_angle <= MAX_ANGLE) {
		m_character_angle = -MAX_ANGLE;
	}
}


void Player::SwimUp() {
	// 上方向への移動量(ベクトルの長さ)を割り出す
	m_move.x += sin(m_character_angle * PI / (float)180.f) * m_speed;
	m_move.y -= cos(m_character_angle * PI / (float)180.f) * m_speed;
}


// 自機と敵との当たり判定後の処理(点滅処理へ移行)
void  Player::HitAction(Type type) {
	Audio& audio = Audio::getInterface();
	// HACK:HitActionは毎フレーム実行されるので注意、無敵できてない
	if (type == ENEMY&&m_is_alive == true) {
		// 数値は仮実装
		// 無敵時間
		m_stamina -= 10;
		auto sound = audio.getBuffer("Resource/Sound/Player/damage.wav");
		sound->Play(0, 0, 0);

		/*GetDamageTimer();*/
	}
}

// 未実装
//void Player::GetDamageTimer() {
//	--invisible_count;
//	if (invisible_count % 25 == 0) {
//		if (m_draw_enable == true) {
//			m_draw_enable = false;
//		}
//		else {
//			m_draw_enable = true;
//		}
//	}
//}
