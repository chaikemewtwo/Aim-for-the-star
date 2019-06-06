#pragma once

#include"../GameObject/Object/Object.h"
#include"../GameObject/ObjectManager/ObjectManager.h"
#include"../Lib/Window/Window.h"


class Blind :public Object {
public:
	Blind();
	~Blind()override {}
	
	void Create(D3DXVECTOR2 pos, D3DXVECTOR2 goal);
	void Update()override;
	void Draw()override;

private:
	void DeleteCheck();
	// 2点の間の角度(ラジアン)を求める関数
	float CalcRadian(float from_x, float from_y, float to_x, float to_y);

// 変数・定数 //
	float m_speed;				// 移動速度
	float m_angle;				// 角度
	D3DXVECTOR2 m_goal_pos;		// 目的地の座標
	int m_anim_change_time;		// 1コマのアニメーションの時間
	int m_max_animation;		// 描画するアニメーションの数
	std::string m_blind_texture;

	const int TEX_PARTITION_NUM = 2;

	// 生存範囲のサイズ《現在は仮の数値を代入》
	const float DELETE_WIDE_MIN = -600;
	const float DELETE_WIDE_MAX = Window::WIDTH + 600;

	ObjectManager* m_pobj_mng;
};
