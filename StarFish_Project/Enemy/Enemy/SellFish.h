#pragma once

#include"EnemyBase.h"


// ほら貝クラス
class SellFish :public EnemyBase {
public:
	SellFish(const D3DXVECTOR2 pos, Map* const map_chip, PlayerManager* const p_mng, bool can_move = true);
	~SellFish()override {}

	void Update()override;
	void Draw()override;
	/*
	ほら貝の遷移
	SideMoveState：指定範囲内にプレイヤーが接近でSideMoveに遷移
	WaitState　　：指定範囲内にプレイヤーが接近で画像のみ変更してWaitStateに遷移
	　　　　　　　 範囲外の場合もWaitStateに遷移
	*/
	StateId CheckChangeState()override;
};
