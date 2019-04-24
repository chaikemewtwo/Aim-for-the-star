#include"EnemyBase.h"

EnemyBase::EnemyBase() {
	m_pos.x = 0.f;
	m_pos.y = 0.f;
	m_dead_timer = 60;
	m_is_dead = false;
}
//―――――――――――――――――――――

void EnemyBase::OutScreen() {
	// 画面外に出たら、削除までの時間をカウントダウン
	if (m_pos.y > WINDOW_H_F || m_pos.x<0 || m_pos.x>WINDOW_W_F) {
		if (m_dead_timer >= 0) {
			m_dead_timer--;
			// 時間が0になったら削除フラグをtrueに
			if (m_dead_timer <= 0) {
				m_is_dead = true;
			}
		}
	}
	// 画面内に戻ったら時間を戻す
	else if (m_pos.y < WINDOW_H_F || m_pos.x>0 || m_pos.x < WINDOW_W_F) {
		m_dead_timer = 60;
	}
}
//―――――――――――――――――――――

float EnemyBase::GetPosX() {
	return m_pos.x;
}

float EnemyBase::GetPosY() {
	return m_pos.y;
}

void EnemyBase::SetPosX(float x) {
	m_pos.x = x;
}

void EnemyBase::SetPosY(float y) {
	m_pos.y = y;
}

float EnemyBase::GetSpeed() {
	return m_speed;
}

bool EnemyBase::IsDead() {
	return m_is_dead;
}

int EnemyBase::GetDeadTimer() {
	return m_dead_timer;
}

int EnemyBase::GetEnemyType() {
	return m_enemy_type;
}
//―――――――――――――――――――――
