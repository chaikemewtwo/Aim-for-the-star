﻿#pragma once

#include"EnemyBase.h"
#include"../../Lib/Window/Window.h"

// ほら貝クラス
class SellFish :public EnemyBase {
public:
	SellFish(D3DXVECTOR2 pos, MapChip* map_chip, bool no_move = false);
	~SellFish() {}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ChangeState(StateBase* state)override;

private:
	StateBase* m_pstate_base;
};
