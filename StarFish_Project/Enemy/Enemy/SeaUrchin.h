#pragma once

#include"EnemyBase.h"


// ウニクラス
class SeaUrchin :public EnemyBase {
public:
	SeaUrchin(D3DXVECTOR2 pos, Map* const map_chip, bool cam_move = true);
	~SeaUrchin()override {}	

	void Update()override;
	void Draw()override;
	StateId CheckChangeState()override;
};
