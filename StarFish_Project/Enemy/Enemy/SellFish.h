#pragma once

#include"EnemyBase.h"


// ほら貝クラス
class SellFish :public EnemyBase {
public:
	SellFish(D3DXVECTOR2 pos, Map* map_chip, PlayerManager* const p_mng, bool can_move = true);
	~SellFish()override {}

	void Update()override;
	void Draw()override;
	StateId CheckChangeState()override;
};
