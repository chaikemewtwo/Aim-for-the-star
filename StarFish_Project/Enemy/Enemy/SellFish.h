#pragma once

#include"EnemyBase.h"


// ほら貝クラス
class SellFish :public EnemyBase {
public:
	SellFish(D3DXVECTOR2 pos, const Map* map_chip, const Player*p1, const Player* p2, bool can_move = true);
	~SellFish()override {}

	void Update()override;
	void Draw()override;
	StateId CheckChangeState()override;
};
