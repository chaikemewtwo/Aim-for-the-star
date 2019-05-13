#pragma once

#include"../GameObject/Object/Object.h"
#include"../GameObject/ObjectManager/ObjectManager.h"


class Blind :public Object {
public:
	enum Direction {
		TOP_RIGHT,
		TOP_LEFT,
		UNDER_RIGHT,
		UNDER_LEFT,
		DIRECTION_NUM
	};

	Blind();
	~Blind() {}
	
	void Create(D3DXVECTOR2 pos);
	void Update();
	void Draw();
	// 仮の削除判定
	void OutScreen();

private:
	float m_speed;
	D3DXVECTOR2 m_move;
	float m_angle;
	int m_anim_change_time;
	int m_max_animation;
	Direction m_pos_direction;
	int m_delete_timer;

	ObjectManager* m_pobj_mng;

	const int TEX_PARTITION_NUM = 2;
};
