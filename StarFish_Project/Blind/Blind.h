#pragma once

#include"../Lib/Window/Window.h"
#include"../GameObject/Object/Object.h"
#include"../GameObject/ObjectManager/ObjectManager.h"


// ブラインドクラス
class Blind :public Object {
public:
	Blind();
	~Blind()override {}
	
	void Update()override;
	void Draw()override;

	// 生成関数　
	/*
	第1：生成位置
	第2：目標地点
	*/
	void Create(const D3DXVECTOR2 pos, const D3DXVECTOR2 goal);

private:
	// 指定の範囲外に出たら生存フラグをfalseにする
	void CheckOutScreen();

	// 2点の間の角度(ラジアン)を求める関数　
	/*
	第1：現在地　
	第2：目標地点
	*/
	float CalcRadian(const D3DXVECTOR2 from, const D3DXVECTOR2 to);

private:
	float m_speed;				// 移動速度
	float m_angle;				// 角度
	D3DXVECTOR2 m_goal_pos;		// 目的地の座標
	std::string m_blind_texture;// 画像
	int m_anim_change_time;		// 1コマのアニメーションの時間
	int m_max_animation;		// 描画するアニメーションの数

	// 統合画像の分割数
	const int TEX_PARTITION_NUM = 2;

	// ブラインドを削除するライン(最小)
	const float DELETE_WIDE_MIN = -600;
	// ブラインドを削除するライン(最大)
	const float DELETE_WIDE_MAX = Window::WIDTH + 600;
};
