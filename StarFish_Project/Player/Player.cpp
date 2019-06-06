#include "Player.h"
#include "PlayerState/PlayerWaitState/PlayerWaitState.h"
#include <cmath>
#include "../Map/MapChip/MapChip.h"
#include "../Lib/Sound/DirectSound.h"



Player::Player(ID_TYPE id) :m_state(PlayerWaitState::GetInstance()) {
	// HACK:メンバイニシャライザを使用しスッキリさせる
	Keybord& kb = Keybord::getInterface();

    // 各パラメータ
	// 当たり判定の半径
	const float PLAYER_COLLSION_RADIUS = 64.f;
	// 移動速度
	const float PLAYER_SPEED = 3.f;

	// 自機2種類の共通部分初期化
	m_radius = PLAYER_COLLSION_RADIUS;

	// 当たり判定位置調整（左上から中央に）
	m_ofset = { PLAYER_COLLSION_RADIUS, PLAYER_COLLSION_RADIUS };

	m_is_active = true;

	m_speed = PLAYER_SPEED;

	m_angle = 0.f;

	// アニメーション番号
	m_animation_count = 0;

	m_move = { 0.f, 0.f };

	// 仮移動量（未実装）
	//m_proto_move = {0.f, 0.f};

	m_stamina = MAX_STAMINA;

	m_draw_enable = true;

	// ソート
	m_sort_object_type = SortObject::PLAYER;

	// 自機1（ヒくん、オレンジの方）の初期化情報
	if (id == STAR_1) {
		// 初期位置
		static const D3DXVECTOR2 STAR_1_FIRST_POS = { Window::WIDTH / 2.f - 200.f, Window::HEIGHT / 2.f + 200.f };

		m_pos = STAR_1_FIRST_POS;

		// 操作、キー入力
		imput_button_name[LEFT_KEY] = 'A';
		imput_button_name[RIGHT_KEY] = 'D';
		imput_button_name[SWIM_KEY] = 'W';
		imput_button_name[PULL_ROPE_KEY] = 'Q';
	
		// 状態画像
		star_texture_name[WAIT_TEXTURE] = "Resource/Texture/Player/de_wait.png";
		star_texture_name[STANDING_WAIT_TEXTURE] = "Resource/Texture/Player/de_standing_wait.png";
		star_texture_name[SWIM_TEXTURE] = "Resource/Texture/Player/de_swim.png";
		//star_texture_name[GRAB_TEXTURE] = "";
		//star_texture_name[PULL_ROPE_TEXTURE] = "";
		star_texture_name[DEATH_TEXTURE] = "Resource/Texture/Player/de_die.png";
	}
	// 自機2（デちゃん、ピンクの方）の初期化情報
	else if (id == STAR_2) {
		// 初期位置
		static const D3DXVECTOR2 STAR_2_FIRST_POS = { Window::WIDTH / 2.f + 200.f, Window::HEIGHT / 2.f + 200.f };

		m_pos = STAR_2_FIRST_POS;

		// 操作、キー入力
		imput_button_name[LEFT_KEY] = VK_LEFT;
		imput_button_name[RIGHT_KEY] = VK_RIGHT;
		imput_button_name[SWIM_KEY] = VK_UP;
		imput_button_name[PULL_ROPE_KEY] = 'M';

		// 状態画像
		star_texture_name[WAIT_TEXTURE] = "Resource/Texture/Player/hi_wait.png";
		star_texture_name[STANDING_WAIT_TEXTURE] = "Resource/Texture/Player/hi_standing_wait.png";
		star_texture_name[SWIM_TEXTURE] = "Resource/Texture/Player/hi_swim.png";
		//star_texture_name[GRAB_TEXTURE] = "";
		//star_texture_name[PULL_ROPE_TEXTURE] = "";
		star_texture_name[DEATH_TEXTURE] = "Resource/Texture/Player/hi_die.png";
	}
	// WaitState初回のみ画像の初期化をしてやる（画像の初期化がWaitStateが生成されるタイミングより遅いため）
	m_player_texture = star_texture_name[WAIT_TEXTURE];

	m_state->Init(this);
}


void Player::Update() {

	// 移動量を初期化（マップの当たり判定で必要）
	m_move = D3DXVECTOR2(0.f,0.f);

	// スタミナ自動回復
	if (m_stamina < MAX_STAMINA && m_is_active == true && swim_enable == false){
		++m_stamina;
	}
	if(m_is_active == true && m_stamina <= 0){
		EnableDead();
	}

	// ステート更新（内部の処理は各ステート内で管理しています）
	m_state->Update(this);

	m_pos += m_move;
}


void Player::Draw() {
	// 描画調整用定数
	// キャラのサイズは128×128ピクセル
	// テクスチャサイズ調整X座標用
	const float TEXTURE_SIZE_X = 0.25f;

	// テクスチャサイズ調整Y座標用
	const float TEXTURE_SIZE_Y = TEXTURE_SIZE_X;

	// 分割画像X枚数
	const int TEXTURE_PARTITION_X_NUMBER = 4;

	// 分割画像Y枚数
	const int TEXTURE_PARTITION_Y_NUMBER = TEXTURE_PARTITION_X_NUMBER;

	// 第7、8引数が0.5fずつで中心座標から描画	
	// 被弾状態は描画する、しないを切り替えて表現する
	if (m_draw_enable == true) {
		Texture::Draw2D(
			m_player_texture.c_str(),
			m_pos.x,
			m_pos.y,
			TEXTURE_SIZE_X,
			TEXTURE_SIZE_Y,
			m_angle,
			0.5f,
			0.5f,
			true,
			TEXTURE_PARTITION_X_NUMBER,
			TEXTURE_PARTITION_Y_NUMBER,
			m_animation_count
		);
	}
}


void Player::AddGravity() {
	m_move.y -= GRAVITY;
}


void Player::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (m_angle <= MAX_ANGLE && m_angle >= -MAX_ANGLE) {
		m_angle += is_move_right ? ANGLE_ADD : -ANGLE_ADD;
	}
	// 角度変更範囲設定
	// 左
	else if (m_angle >= MAX_ANGLE) {
		m_angle = MAX_ANGLE;
	}
	// 右
	else if (m_angle < MAX_ANGLE) {
		m_angle = -MAX_ANGLE;
	}
}


void Player::SwimUp() {
	static const float RAD = 180.f;
	// 上方向への移動量(ベクトルの長さ)を割り出す
	m_move.x += sin(m_angle * PI / RAD) * m_speed;
	m_move.y -= cos(m_angle * PI / RAD) * m_speed;
}


// 自機と敵との当たり判定後の処理(点滅処理へ移行)
void  Player::HitAction(Type type) {
	// HACK:HitActionは毎フレーム実行されるので注意、無敵はフラグ等を立てて実装する
	if (type == ENEMY&&m_is_active == true) {
		const int DECREASE_STAMINA = 10;
		DecStamina(DECREASE_STAMINA);
		Audio& audio = Audio::getInterface();
		auto sound = audio.getBuffer("Resource/Sound/Player/damage.wav");
		sound->Play(0, 0, 0);
		// 無敵時間
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


D3DXVECTOR2 Player::GetMove()const {
	return m_move;
}


void Player::SetPos(D3DXVECTOR2 pos) {
	m_pos = pos;
}


void Player::SetMove(D3DXVECTOR2 move) {
	m_move = move;
}


void Player::AddMove(D3DXVECTOR2 add_move) {
	m_move += add_move;
}


void Player::ChangeState(PlayerStateBase* state) {
	m_state = state;
	m_state->Init(this);
}


void Player::ResetAnimationNumber() {
	m_animation_count = 0;
}


void Player::SetPlayerTexture(std::string new_player_texture) {
	m_player_texture = new_player_texture;
}


int Player::GetStateChangeTimer() {
	return m_state_change_timer;
}


void Player::ResetStateChangeTimer() {
	m_state_change_timer = 0;
}


void Player::AddStateChangeTimer() {
	++m_state_change_timer;
}


int Player::GetStamina() {
	return m_stamina;
}


void Player::DecStamina(int dec_sutamina_num) {
	m_stamina -= dec_sutamina_num;
}


void Player::EnableDead() {
	m_is_active = false;
}
