#include "Player.h"
#include "PlayerState/PlayerWaitState/PlayerWaitState.h"
#include "../Map/MapChip/MapChip.h"
#include <cmath>


const float Player::PLAYER_COLLSION_RADIUS = 64.f;
const float Player::PLAYER_SPEED = 3.f;
const D3DXVECTOR2 Player::STAR_1_FIRST_POS = { Window::WIDTH / 2.f - 200.f, Window::HEIGHT / 2.f + 200.f };
const D3DXVECTOR2 Player::STAR_2_FIRST_POS = { Window::WIDTH / 2.f + 200.f, Window::HEIGHT / 2.f + 200.f };
const D3DXVECTOR2 Player::TEXTURE_SIZE_OFFSET = { 0.25f, 0.25f };
const D3DXVECTOR2 Player::TEXTURE_PARTITION = { 4.f,4.f };
const int Player::DECREASE_STAMINA = 300;


Player::Player(ID_TYPE id) :
	m_p_state(PlayerWaitState::GetInstance()), // 
	m_move(0.f, 0.f),
	m_angle(0.f),
	m_draw_enable(true),
	m_is_hit(false)
	{
	// 自機2種類の共通部分の初期化
	// 当たり判定の半径
	m_radius = PLAYER_COLLSION_RADIUS;

	// 当たり判定位置調整（左上から中央に）
	m_offset = { PLAYER_COLLSION_RADIUS, PLAYER_COLLSION_RADIUS };

	m_speed = PLAYER_SPEED;	

	m_stamina = MAX_STAMINA;

	// 仮移動量（未実装）
	//m_proto_move = {0.f, 0.f};

	// ソート
	m_sort_object_type = SortObject::PLAYER;

	m_p_hit_se = m_p_audio.getBuffer("Resource/Sound/Player/damage.wav");

	// 自機1（ヒくん、オレンジの方）の初期化情報
	if (id == STAR_1) {
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

	m_p_state->Init(this);
}


void Player::Update() {

	// 移動量を初期化（マップの当たり判定で使用）
	m_move = D3DXVECTOR2(0.f,0.f);

	// スタミナ自動回復
	if (m_stamina < MAX_STAMINA && m_is_active == true && swim_enable == false){
		++m_stamina;
	}
	if(m_is_active == true && m_stamina <= 0){
		EnableDead();
	}

	// ステート更新（内部の処理は各ステート内で管理しています）
	m_p_state->Update(this);

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
			TEXTURE_SIZE_OFFSET.x,
			TEXTURE_SIZE_OFFSET.y,
			m_angle,
			0.5f,
			0.5f,
			true,
			(int)TEXTURE_PARTITION.x,
			(int)TEXTURE_PARTITION.y,
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
		DecStamina(DECREASE_STAMINA);
		m_p_hit_se->Play(0,0,0);
		m_is_hit = true;
	}
	m_is_hit = false;
}


// 未実装
//void Player::GetDamageTimer() {
//	--invisible_count;
//	/*if (m_is_hit != prev_is_hit) {
//	
//	}
//	if (invisible_count % 25 == 0) {
//		m_draw_enable == true ? false : true;
//	}*/
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
	m_p_state = state;
	m_p_state->Init(this);
}


void Player::ResetAnimationCount() {
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
