﻿#pragma once

#include"EnemyBase.h"


class NaporeonFish :public EnemyBase {
public:
	NaporeonFish(D3DXVECTOR2 pos, Map* map, PlayerManager * p_mng, bool can_move = false);
	~NaporeonFish()override {}

	void Update()override;
	void Draw()override;
	StateId StateChangeCheck()override;

private:
	static const int CHASE_RANGE = 200;
};
