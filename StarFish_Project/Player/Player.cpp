#include "Player.h"
#include "PlayerState/PlayerWaitState/PlayerWaitState.h"
#include "PlayerState/PlayerSwimState/PlayerSwimState.h"
#include "PlayerState/PlayerStandingWaitState/PlayerStandingWaitState.h"
#include <cmath>
#include <time.h>


Player::Player() :m_state(PlayerWaitState::GetInstance()) {
	// 移動速度
	m_speed = 2.f;

	// 傾き
	m_character_angle = 0.f;

	// アニメーション番号
	m_animation_num = 0;


	// 移動量
	m_move.x = 0.f;
	m_move.y = 0.f;

	// 待機状態初期化
	m_state->Init(this);

	// スタミナ
	m_stamina = MAX_SUTAMINA;

	// 描画フラグ
	m_draw_enable = true;
}


void Player::Update() {
	// 移動を加算
	m_pos += m_move;

	// 移動量を初期化（マップの当たり判定で必要）
	m_move.x = 0.f;
	m_move.y = 0.f;

	// スタミナ自動回復
	if (m_stamina <= MAX_SUTAMINA) {
		++m_stamina;
	}
	else {
		m_stamina = MAX_SUTAMINA;
	}

	// ステート更新
	// 内部の処理は各ステート内で管理しています
	m_state->Update(this);
}


void Player::Draw() {
	// 自機2にも自機1のものを使用中
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
	m_move.y += GRAVITY;
}


void Player::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (m_character_angle <= MAX_ANGLE && m_character_angle >= -MAX_ANGLE) {
		m_character_angle += is_move_right ? ANGLE_ADD : -ANGLE_ADD;
	}
	// 角度変更範囲設定
	// 
	else if (m_character_angle >= MAX_ANGLE) {
		m_character_angle = MAX_ANGLE;
	}
	else if (m_character_angle <= MAX_ANGLE) {
		m_character_angle = -MAX_ANGLE;
	}
}


void Player::SwimUp() {

	// 上方向への移動量(ベクトルの長さ)を割り出す
	m_move.x += sin(m_character_angle * PI / (float)180.f) * m_speed;
	m_move.y += cos(m_character_angle * PI / (float)180.f) * m_speed;


	// 移動量インクリメント
	//m_pos.x += m_move.x;
	//m_pos.y -= m_move.y;
}


// 自機と敵との当たり判定後の処理(点滅処理へ移行)
void  Player::HitAction(Type type) {
	if (type == ENEMY) {
		
	}
}
