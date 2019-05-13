#pragma once

#include"../GameObject/Object/Object.h"
#include"../GameObject/ObjectManager/ObjectManager.h"
#include"../Lib/Window/Window.h"


class Blind :public Object {
public:
	// 位置方向を指す定数　《変更予定》
	enum Direction {
		TOP_RIGHT,
		TOP_LEFT,
		UNDER_RIGHT,
		UNDER_LEFT,
		DIRECTION_NUM
	};

	Blind();
	~Blind() {}
	
	void Create(D3DXVECTOR2 pos, D3DXVECTOR2 goal);
	void Update();
	void Draw();
	void DeleteJudg();
	float GetRad();

private:
	float m_speed;				// 移動速度
	float m_angle;				// 角度
	D3DXVECTOR2 m_goal_pos;		// 目的地の座標
	Direction m_pos_direction;	// 現在の描画位置方向
	int m_anim_change_time;		// 1コマのアニメーションの時間
	int m_max_animation;		// 描画するアニメーションの数

	ObjectManager* m_pobj_mng;	

	const int TEX_PARTITION_NUM = 2;
	// 生存範囲のサイズ(仮の数値を代入)
	const float DELETE_WIDE_MIN = -200;
	const float DELETE_WIDE_MAX = WINDOW_W_F + 200;
};
