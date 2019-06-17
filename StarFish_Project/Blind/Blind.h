#pragma once

#include"../GameObject/Object/Object.h"
#include"../GameObject/ObjectManager/ObjectManager.h"
#include"../Lib/Window/Window.h"


class Blind :public Object {
public:
	Blind();
	~Blind()override {}
	
	void Update()override;
	void Draw()override;

	// 生成関数　引数に初期位置と目指す位置を渡す
	void Create(D3DXVECTOR2 pos, D3DXVECTOR2 goal);

private:
	// 指定の範囲外に出たら生存フラグをfalseにする
	void CheckOutScreen();

	// 2点の間の角度(ラジアン)を求める関数　第1：現在地　第2：目標地点
	float CalcRadian(D3DXVECTOR2 from, D3DXVECTOR2 to);

private:
	float m_speed;				// 移動速度
	float m_angle;				// 角度
	D3DXVECTOR2 m_goal_pos;		// 目的地の座標
	int m_anim_change_time;		// 1コマのアニメーションの時間
	int m_max_animation;		// 描画するアニメーションの数
	std::string m_blind_texture;// 画像用の変数

	// 統合画像の分割数
	const int TEX_PARTITION_NUM = 2;

	// 生存範囲のサイズ
	const float DELETE_WIDE_MIN = -700;
	const float DELETE_WIDE_MAX = Window::WIDTH + 700;
};
