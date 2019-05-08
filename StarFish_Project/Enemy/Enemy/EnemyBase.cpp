﻿#include"../../Lib/Window/Window.h"
#include"EnemyBase.h"

EnemyBase::EnemyBase() {
	m_delete_timer = 60;
	//m_animation_timer = 0;
	m_max_animation = 0;
}
//―――――――――――――――――――――

void EnemyBase::OutScreen() {
	// 画面外に出たら、削除までの時間をカウントダウン
	if (m_pos.y > WINDOW_H_F || m_pos.x<0 || m_pos.x>WINDOW_W_F) {
		if (m_delete_timer >= 0) {
			m_delete_timer--;
			// 時間が0になったら削除フラグをtrueに
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

// Object反映のためコメントアウト　《要/調整》
/*void EnemyBase::AnimationDraw(int max_animation, int anim_cange_time) {
	if (m_animation_timer >= anim_cange_time) {
		m_animation_timer = 0;
		m_animation_num++;
		// 描画する画像番号が分割後の使用枚数を超えたら、番号を初期化
		if (m_animation_num >= max_animation) {
			m_animation_num = 0;
		}
	}
	else {
		m_animation_timer++;
	}
}*/
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
