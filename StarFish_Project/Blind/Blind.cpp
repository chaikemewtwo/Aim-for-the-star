﻿#include<cmath>
#include"Blind.h"
#include"../Lib/Texture/TextureBoad2D.h"


Blind::Blind() {

	// 変数の初期化
	m_pos = { 0,0 };
	m_goal_pos = { 0,0 };
	m_speed = 3.f;
	m_angle = 0.f;
	m_animation_count = 0;
	m_max_animation = 3;
	m_anim_change_time = 15;

	// 画像ソート用のID登録
	m_sort_object_type = SortObjectType::BLIND;

	// 画像の登録
	m_blind_texture = "Resource/Texture/Blind/blind.png";
}
//―――――――――――――――――――――――

// 生成
void Blind::Create(const D3DXVECTOR2 pos, const D3DXVECTOR2 goal) {

	// 生成位置と目的地を設定
	m_pos = pos;
	m_goal_pos = goal;

	// 移動方向に画像が向いているように設定(Draw2D使用のために角度に直す)
	m_angle = ((CalcRadian(m_pos, m_goal_pos) * 180) / D3DX_PI) + 180;
}
//―――――――――――――――――――――――

// 更新
void Blind::Update() {

	CheckOutScreen();

	// 現在地と目的地のラジアンを求める
	float radian = CalcRadian(m_pos, m_goal_pos);

	// 受け取ったラジアンで、目的地に向けて移動
	m_pos.y += sinf(radian)*m_speed;
	m_pos.x += cosf(radian)*m_speed;
}
//―――――――――――――――――――――――

// 2点の角度を求める
float Blind::CalcRadian(const D3DXVECTOR2 from, const D3DXVECTOR2 to) {

	float rad = atan2((to.y - from.y), (to.x - from.x));
	return rad;
}
//―――――――――――――――――――――――

// 削除フラグのチェック
void Blind::CheckOutScreen() {

	// 指定範囲内ならtrue、範囲外ならfalse
	if (m_pos.x < DELETE_WIDE_MIN || m_pos.x > DELETE_WIDE_MAX) {
		m_is_active = false;
	}
	else if (m_pos.x > DELETE_WIDE_MIN || m_pos.x < DELETE_WIDE_MAX) {
		m_is_active = true;
	}
}
//―――――――――――――――――――――――

void Blind::Draw() {

	// 目的地の座標に合わせて画像を反転させるかどうか
	if (m_goal_pos.x < 0) {
		Texture::Draw2D(
			m_blind_texture.c_str(),
			m_pos.x, m_pos.y,
			0.5f, 0.5f,
			m_angle, 0.5f, 0.5f,
			true, TEX_PARTITION_NUM, TEX_PARTITION_NUM,
			m_animation_count
		);
	}
	else if (m_goal_pos.x > Window::WIDTH) {
		Texture::Draw2D(
			m_blind_texture.c_str(),
			m_pos.x, m_pos.y,
			0.5f, 0.5f,
			m_angle, 0.5f, 0.5f,
			true, TEX_PARTITION_NUM, TEX_PARTITION_NUM,
			m_animation_count,
			0, 0,
			Texture::MIRROR
		);
	}

	// アニメーションの更新
	AnimationCount(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――
