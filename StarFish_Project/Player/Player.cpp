﻿#include "Player.h"
#include "PlayerState/PlayerWaitState/PlayerWaitState.h"
#include "../Map/Map/Map.h"
#include <cmath>

// 値を変えてもよいパラメータ
// HACK:csvを使用し外部で指定できるようにする
const float Player::PLAYER_COLLSION_RADIUS = 25.f;
const float Player::PLAYER_SPEED = 3.f;
const float Player::GRAVITY = 1.f;
const float Player::ANGLE_ADD = 0.5f;
const float Player::MAX_ANGLE = 45.f;
const float Player::MAX_STAMINA = 750.f;
const float Player::DECREASE_STAMINA = 300.f;
const int Player::MAX_INVISIBLE_COUNT = 180;
const int Player::INVISIBLE_DRAW_SWITCH_TIME = 15;


Player::Player(ID_TYPE id, D3DXVECTOR2 first_pos) :
	m_p_state(PlayerWaitState::GetInstance()),
	m_move(0.f, 0.f),
	m_angle(0.f),
	m_draw_enable(true),
	m_swim_enable(false),
	m_invisible_count(0),
	m_stamina(MAX_STAMINA),
	m_rope_pull_enable(false)
{
	// 自機2種類の共通部分の初期化

	// 当たり判定の半径
	m_radius = PLAYER_COLLSION_RADIUS;

	// 当たり判定位置調整（左上から中央に）
	m_hit_vertex_offset = { 64.f, 64.f };

	m_speed = PLAYER_SPEED;

	// 描画順ソート
	m_sort_object_type = SortObjectType::PLAYER;

	m_p_hit_se = m_p_audio.getBuffer("Resource/Sound/Player/damage.wav");

	// 操作、キー入力
	if (id == STAR_1) {
		command_list[KEY_LEFT] = m_p_game_input->P1_LEFT_BUTTON;
		command_list[KEY_RIGHT] = m_p_game_input->P1_RIGHT_BUTTON;
		command_list[KEY_SWIM] = m_p_game_input->P1_DECIDE_BUTTON;
	}
	else if (id == STAR_2) {
		command_list[KEY_LEFT] = m_p_game_input->P2_LEFT_BUTTON;
		command_list[KEY_RIGHT] = m_p_game_input->P2_RIGHT_BUTTON;
		command_list[KEY_SWIM] = m_p_game_input->P2_DECIDE_BUTTON;
	}

	// 画像
	std::string both_texture_list[MAX_TYPE][MAX_TEXTURE_NUM] = {
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

	// 上記の画像を格納
	for (int i = 0; i < MAX_TEXTURE_NUM; i++) {
		texture_list[i] = both_texture_list[id][i];
	}

	// WaitState初回のみ画像の初期化をしてやる
	// 画像の初期化がWaitStateが生成されるタイミングより遅いため
	SetPlayerTexture(WAIT_TEXTURE);

	m_pos = first_pos;

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

	// 被弾したときに無敵タイマーがカウントされる
	InvisibleCount();

	// ステート更新（内部の処理は各ステート内で管理しています）
	m_p_state->Update(this);
}


void Player::Draw() {
	// 統合画像を切り取る枚数
	static const D3DXVECTOR2 TEXTURE_PARTITION = { 4.f,4.f };
	// 統合画像ピクセル数
	static const D3DXVECTOR2 TEXTURE_SIZE_OFFSET = { 1.f/ TEXTURE_PARTITION.x, 1.f / TEXTURE_PARTITION.y };
	
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


Player* Player::GetInstance() {
	return this;
}


void Player::AddGravity() {
	// 重力フラグを判別
	m_move.y += GRAVITY;
}


void Player::AngleAdjust(bool is_move_right) {
	// 自機角度変更、TRUEで右へ傾く
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
	// 向いている角度とスピードから移動量を割り出し加算（移動量は毎フレーム0リセットしています）
	m_move.x += sin(m_angle * D3DX_PI / 180.f) * m_speed;
	m_move.y -= cos(m_angle * D3DX_PI / 180.f) * m_speed;
}


void  Player::HitAction(Type type) {

	if (type == COLLISION_OBJECT_ENEMY&&m_is_active == true&& m_invisible_count <= 0) {
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
	// 描画ON
	if (m_is_active == false ||(m_invisible_count / INVISIBLE_DRAW_SWITCH_TIME) % 2 == 0) {
		m_draw_enable = true;
	}
	// 描画OFF
	else if ((m_invisible_count / INVISIBLE_DRAW_SWITCH_TIME) % 2 == 1) {
		m_draw_enable = false;
	}
}


D3DXVECTOR2 Player::GetMove()const {
	return m_move;
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
	m_player_texture = texture_list[new_state_texture];
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


GameInput::INPUT_BUTTON Player::GetStarInput(STAR_INPUT num) {
	return command_list[num];
}
