#include"../../Lib/Window/Window.h"
#include"../State/EnemyWaitState.h"
#include"EnemyBase.h"


EnemyBase::EnemyBase() {
	m_angle = 0;
	m_center = 0;
	m_delete_timer = 60;
	m_max_animation = 0;
	m_enemy_type = ENEMY_TYPE_MAX;
	m_stateid = STATEID_MAX;
	m_pstate_base = Wait::GetInstance();
}
//―――――――――――――――――――――

void EnemyBase::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――

void EnemyBase::OutScreen() {
	// 画面外に出たら、削除までの時間をカウントダウン
	if (m_pos.y > WINDOW_H_F || m_pos.x<0 || m_pos.x>WINDOW_W_F) {
		if (m_delete_timer >= 0) {
			m_delete_timer--;
			if (m_delete_timer <= 0) {
				m_is_active = false;
			}
		}
	}
	// 画面内に戻ったら時間を戻す
	else if (m_pos.y < WINDOW_H_F || m_pos.x>0 || m_pos.x < WINDOW_W_F) {
		m_delete_timer = 60;
	}
}
//―――――――――――――――――――――

float EnemyBase::CalcDistance() {
	float player1_y_distance = 0;
	float player2_y_distance = 0;

	// 自身がプレイヤーよりも上にいる場合
	if (m_pplayer1->GetPos().y > m_pos.y&&m_pplayer2->GetPos().y > m_pos.y) {
		player1_y_distance = m_pplayer1->GetPos().y - m_pos.y;
		player2_y_distance = m_pplayer2->GetPos().y - m_pos.y;
	}
	// 自身がプレイヤーよりも下にいる場合
	else if (m_pplayer1->GetPos().y < m_pos.y&&m_pplayer2->GetPos().y < m_pos.y) {
		player1_y_distance = m_pos.y - m_pplayer1->GetPos().y;
		player2_y_distance = m_pos.y - m_pplayer2->GetPos().y;
	}

	// より近いほうの距離を返す
	if (player1_y_distance < player2_y_distance) {
		return player1_y_distance;
	}
	return player2_y_distance;
}
//―――――――――――――――――――――

EnemyBase* EnemyBase::GetInstance() {
	return this;
}
//―――――――――――――――――――――

float EnemyBase::GetSpeed() {
	return m_speed;
}

int EnemyBase::GetPower() {
	return m_power;
}

bool EnemyBase::NoMove() {
	return m_no_move;
}

bool EnemyBase::IsLeft() {
	return m_is_left;
}

int EnemyBase::GetEnemyType() {
	return m_enemy_type;
}

void EnemyBase::SetStateId(StateId state_id) {
	m_stateid = state_id;
}
//―――――――――――――――――――――
