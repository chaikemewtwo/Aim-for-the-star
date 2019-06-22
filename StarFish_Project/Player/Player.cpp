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
const float Player::GRAVITY = 1.f;
const float Player::ANGLE_ADD = 0.5f;
const float Player::MAX_ANGLE = 45.f;
const float Player::MAX_STAMINA = 1000.f;
const float Player::DECREASE_STAMINA = 300.f;
const int Player::MAX_INVISIBLE_COUNT = 180;
const int Player::INVISIBLE_DRAW_SWITCH_TIME = 20;


Player::Player(ID_TYPE id) :
	m_p_state(PlayerWaitState::GetInstance()),
	m_move(0.f, 0.f),
	m_angle(0.f),
	m_draw_enable(true),
	m_invisible_count(0),
	m_stamina(MAX_STAMINA)
	{
	// 自機2種類の共通部分の初期化

	// 当たり判定の半径
	m_radius = PLAYER_COLLSION_RADIUS;

	// 当たり判定位置調整（左上から中央に）
	m_offset = { PLAYER_COLLSION_RADIUS, PLAYER_COLLSION_RADIUS };

	m_speed = PLAYER_SPEED;	

	// 描画順ソート
	m_sort_object_type = SortObject::PLAYER;

	m_p_hit_se = m_p_audio.getBuffer("Resource/Sound/Player/damage.wav");

	// 操作、キー入力
	char input_list[MAX_TYPE][MAX_KEY_NUM] = {
		// 自機1
		{ 'A', 'D', 'W', 'Q'},

		// 自機2
		{ VK_LEFT, VK_RIGHT, VK_UP, 'M' }
	};

	// 上記のキー入力を代入
	for (int i = 0; i < MAX_KEY_NUM; i++){
		imput_button_list[i] = input_list[id][i];
	}

	// 画像
	std::string texture_list[MAX_TYPE][MAX_KEY_NUM] = {
		// 自機1
		{ "Resource/Texture/Player/de_wait.png",
		"Resource/Texture/Player/de_standing_wait.png",
		"Resource/Texture/Player/de_swim.png",
		"Resource/Texture/Player/de_die.png" },

		// 自機2
		{ "Resource/Texture/Player/hi_wait.png",
		"Resource/Texture/Player/hi_standing_wait.png",
		"Resource/Texture/Player/hi_swim.png",
		"Resource/Texture/Player/hi_die.png" }
	};

	// 上記の画像を代入
	for (int i = 0; i < MAX_KEY_NUM; i++) {
		star_texture_list[i] = texture_list[id][i];
	}

	// WaitState初回のみ画像の初期化をしてやる
	// 画像の初期化がWaitStateが生成されるタイミングより遅いため
	SetPlayerTexture(WAIT_TEXTURE);

	// 自機1（ヒくん、オレンジの方）の初期化情報
	if (id == STAR_1) {
		m_pos = STAR_1_FIRST_POS;
	}
	// 自機2（デちゃん、ピンクの方）の初期化情報
	else if (id == STAR_2) {
		m_pos = STAR_2_FIRST_POS;
	}	

	m_p_state->Init(this);
}


void Player::Update() {
	// 移動量を座標に加算
	m_pos += m_move;

	// 移動量を初期化（マップの当たり判定で使用）
	m_move = { 0.f,0.f };

	// スタミナ自動回復
	if (m_stamina < MAX_STAMINA && m_is_active == true && m_swim_enable == false){
		++m_stamina;
	}

	// スタミナが切れたら死亡フラグを有効にする
	if(m_is_active == true && m_stamina <= 0){
		EnableDead();
	}

	// 無敵時間
	// ずっとUpdate内で回ってるのがよろしくないかも　19/06/18
	InvisibleCount();

	// ステート更新（内部の処理は各ステート内で管理しています）
	m_p_state->Update(this);
}


void Player::Draw() {
	// 第7、8引数が0.5fずつで中心座標から描画	
	// 被弾状態は描画する、しないを切り替えて表現します
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
	m_move.y += GRAVITY;
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
	m_move.x += sin(m_angle * D3DX_PI / RAD) * m_speed;
	m_move.y -= cos(m_angle * D3DX_PI / RAD) * m_speed;
}


void  Player::HitAction(Type type) {
	// HACK:HitActionは毎フレーム実行されるので注意、無敵はフラグ等を立てて実装する
	if (type == ENEMY&&m_is_active == true&& m_invisible_count <= 0) {
		DecStamina(DECREASE_STAMINA);
		m_p_hit_se->Play(0,0,0);
		m_invisible_count = MAX_INVISIBLE_COUNT;
	}
}


void Player::InvisibleCount() {
	if (m_invisible_count > 0) {
		--m_invisible_count;
		InvisibleDrawSwitch();
	}
}


void Player::InvisibleDrawSwitch() {
	// 描画する
	if ((m_invisible_count / INVISIBLE_DRAW_SWITCH_TIME) % 2 == 0) {
		m_draw_enable = true;
	}
	// 描画しない
	else if ((m_invisible_count / INVISIBLE_DRAW_SWITCH_TIME) % 2 == 1) {
		m_draw_enable = false;
	}
	// 死んだらずっと描画
	if (m_is_active == false) {
		m_draw_enable = true;
	}
}


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


void Player::SetPlayerTexture(PLAYER_STATE_TEXTURE new_state_texture) {
	m_player_texture = star_texture_list[new_state_texture];
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


float Player::GetStamina() {
	return m_stamina;
}


void Player::DecStamina(float dec_sutamina_num) {
	m_stamina -= dec_sutamina_num;
}


bool Player::SwimEnable() {
	return m_swim_enable;
}


void Player::SetSwimEnable(bool new_swim_enable) {
	m_swim_enable = new_swim_enable;
}


float Player::StaminaParcentage() {
	return  m_stamina / MAX_STAMINA;
}


void Player::EnableDead() {
	m_is_active = false;
}
