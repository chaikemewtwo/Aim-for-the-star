#include<cmath>
#include"Blind.h"
#include"../Lib/Texture/TextureBoad2D.h"


Blind::Blind() {

	m_pos = D3DXVECTOR2(0,0);
	m_goal_pos = D3DXVECTOR2(0, 0);
	m_speed = 3;
	m_angle = 0;
	m_animation_count = 0;
	m_max_animation = 3;
	m_anim_change_time = 15;
	m_sort_object_type = SortObject::BLIND;
	m_blind_texture = "Resource/Texture/Blind/blind.png";
}
//―――――――――――――――――――――――

void Blind::Create(D3DXVECTOR2 pos, D3DXVECTOR2 goal) {

	// 生成位置と目的地を設定
	m_pos = pos;
	m_goal_pos = goal;

	// 移動方向に画像が向いているように設定(Draw2D使用のために角度に直す)
	m_angle = ((CalcRadian(m_pos.x, m_pos.y, m_goal_pos.x, m_goal_pos.y) * 180) / PI) + 180;
}
//―――――――――――――――――――――――

void Blind::Update() {

	DeleteCheck();

	// 現在地と目的地のラジアンを求める
	float radian = CalcRadian(m_pos.x, m_pos.y, m_goal_pos.x, m_goal_pos.y);

	// 受け取ったラジアンで、目的地に向けて移動
	m_pos.y += sinf(radian)*m_speed;
	m_pos.x += cosf(radian)*m_speed;
}
//―――――――――――――――――――――――

// 引数に求めたい角度の2点を入れる　(第1引数＝現在地、第二引数＝目的地)
float Blind::CalcRadian(float from_x, float from_y, float to_x, float to_y) {

	float rad = atan2((to_y - from_y), (to_x - from_x));
	return rad;
}
//―――――――――――――――――――――――

// 指定した左右位置(定数)を超えたら削除フラグをたたせる
void Blind::DeleteCheck() {

	if (m_pos.x<DELETE_WIDE_MIN || m_pos.x>DELETE_WIDE_MAX) {
		m_is_active = false;
	}
	else if (m_pos.x > DELETE_WIDE_MIN || m_pos.x < DELETE_WIDE_MAX) {
		m_is_active = true;
	}
}
//―――――――――――――――――――――――

void Blind::Draw() {

	Texture::Draw2D(
		m_blind_texture.c_str(),
		m_pos.x, m_pos.y,
		0.5, 0.5, 
		m_angle, 0.5, 0.5,
		true, TEX_PARTITION_NUM, TEX_PARTITION_NUM,
		m_animation_count
	);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――
