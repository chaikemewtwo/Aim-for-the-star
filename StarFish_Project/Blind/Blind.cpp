#include<cmath>
#include"Blind.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Window/Window.h"


Blind::Blind() {
	m_speed = 5;
	m_angle = 0;
	
	m_anim_change_time = 20;
	m_max_animation = 2;
	m_pos_direction = DIRECTION_NUM;
	m_delete_timer = 60;
}
//―――――――――――――――――――――――

void Blind::Create(D3DXVECTOR2 pos) {
	m_pos = pos;
	//m_angle += GetRad();
	// 現在の位置に当てはまるものを代入
	if (m_pos.x < (WINDOW_W_F / 2) && m_pos.y < (WINDOW_H_F / 2)) {
		m_pos_direction = TOP_LEFT;
		m_angle = 190;
	}
	else if (m_pos.x > (WINDOW_W_F / 2) && m_pos.y < (WINDOW_H_F / 2)) {
		m_pos_direction = TOP_RIGHT;
		m_angle = -30;
	}
	else if (m_pos.x<(WINDOW_W_F / 2) && m_pos.y>(WINDOW_H_F / 2)) {
		m_pos_direction = UNDER_LEFT;
		m_angle = 160;
	}
	else if (m_pos.x > (WINDOW_W_F / 2) && m_pos.y > (WINDOW_H_F / 2)) {
		m_pos_direction = UNDER_RIGHT;
		m_angle = 30;
	}
}
//―――――――――――――――――――――――

void Blind::Update() {
	m_move.x = 0;
	m_move.y = 0;
	OutScreen();
	switch (m_pos_direction) {
	case TOP_LEFT:
		//m_move.x += sin(m_angle * PI / (float)360.f) * m_speed;
		//m_move.y -= cos(m_angle * PI / (float)180.f) * m_speed;
		m_pos.x += m_speed;
		m_pos.y += m_speed / 2;
		break;
	case TOP_RIGHT:		
		m_pos.x -= m_speed;
		m_pos.y += m_speed / 2;
		break;
	case UNDER_LEFT:
		m_pos.x += m_speed;
		m_pos.y -= m_speed / 2;
		break;
	case UNDER_RIGHT:
		m_pos.x -= m_speed;
		m_pos.y -= m_speed / 2;
		break;
	}
	//m_pos += m_move;
}

//―――――――――――――――――――――――

void Blind::OutScreen() {
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
//―――――――――――――――――――――――

void Blind::Draw() {
	// ブラインドの小魚を描画(アニメーションあり)
	Texture::Draw2D(
		"Resource/hora_ready.png",
		m_pos.x, m_pos.y,
		1, 1, m_angle, 0.5, 0.5,
		true, TEX_PARTITION_NUM, TEX_PARTITION_NUM,
		m_animation_num);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――

