#pragma once

#include"EnemyBase.h"
#include"../../Lib/Window/Window.h"


// ほら貝クラス
class SellFish :public EnemyBase {
public:
	SellFish(D3DXVECTOR2 pos, Map* map_chip, Player*p1, Player* p2, bool can_move = true);
	~SellFish()override {}

	void Update()override;
	void Draw()override;
	StateId StateChangeCheck()override;
};
