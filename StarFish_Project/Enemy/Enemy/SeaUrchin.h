#pragma once

#include"EnemyBase.h"


// ウニクラス
class SeaUrchin :public EnemyBase {
public:
	// コンストラクタの引数に初期位置を入れる
	SeaUrchin(D3DXVECTOR2 pos, Map* map_chip, bool no_move = false);
	~SeaUrchin()override {}	

	void Update()override;
	void Draw()override;
	StateId StateChangeCheck()override;
};
