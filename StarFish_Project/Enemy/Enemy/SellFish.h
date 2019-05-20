#pragma once

#include"EnemyBase.h"
#include"../../Lib/Window/Window.h"

// ほら貝クラス
class SellFish :public EnemyBase {
public:
	SellFish(D3DXVECTOR2 pos, MapChip* map_chip, Player*p1, Player* p2, bool no_move = false);
	~SellFish() {}

	void Update()override;
	void Draw()override;
	StateId IsStateChangeCheck()override;
};
