#pragma once

#include"EnemyBase.h"


// ほら貝クラス
class SellFish :public EnemyBase {
public:
	SellFish(D3DXVECTOR2 pos, Map* map_chip, Player*p1, Player* p2, bool can_move = true);
	~SellFish()override {}

	void Update()override;
	void Draw()override;
	StateId StateChangeCheck()override;
	
private:
	// 攻撃範囲の距離
	static const int ATTACK_RANGE = 200;
	// 攻撃前の準備状態の範囲距離
	static const int ATTACK_READY_RANGE = 350;
};
