#include<cmath>
#include"Blind.h"
#include"../Lib/Texture/TextureBoad2D.h"


Blind::Blind() {
	m_speed = 5;
	m_angle = 0;
	m_anim_change_time = 20;
	m_max_animation = 2;
	m_pos_direction = DIRECTION_NUM;
}
//―――――――――――――――――――――――

void Blind::Create(D3DXVECTOR2 pos, D3DXVECTOR2 goal) {
	// 生成位置と目的地を設定
	m_pos = pos;
	m_goal_pos = goal;
	// 移動方向に向かせたい《途中》
	m_angle = (GetRad()*180)/PI;

	// 現在の位置に当てはまるものを代入
	if (m_pos.x < (WINDOW_W_F / 2) && m_pos.y < (WINDOW_H_F / 2)) {
		m_pos_direction = TOP_LEFT;
	}
	else if (m_pos.x > (WINDOW_W_F / 2) && m_pos.y < (WINDOW_H_F / 2)) {
		m_pos_direction = TOP_RIGHT;
	}
	else if (m_pos.x<(WINDOW_W_F / 2) && m_pos.y>(WINDOW_H_F / 2)) {
		m_pos_direction = UNDER_LEFT;
	}
	else if (m_pos.x > (WINDOW_W_F / 2) && m_pos.y > (WINDOW_H_F / 2)) {
		m_pos_direction = UNDER_RIGHT;
	}
}
//―――――――――――――――――――――――

void Blind::Update() {
	DeleteJudg();

	// 現在地と目的地のラジアンを求める
	float rad = GetRad();
	// 受け取ったラジアンで、目的地に向けて移動
	m_pos.y += sinf(rad)*m_speed;
	m_pos.x += cosf(rad)*m_speed;
}
//―――――――――――――――――――――――

float Blind::GetRad() {
	float num = atan2((m_goal_pos.y - m_pos.y), (m_goal_pos.x - m_pos.x));
	return num;
}
//―――――――――――――――――――――――

void Blind::DeleteJudg() {
	if (m_pos.x<DELETE_WIDE_MIN || m_pos.x>DELETE_WIDE_MAX) {
		m_is_active = false;
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

