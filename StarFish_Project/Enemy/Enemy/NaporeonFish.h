#pragma once

#include"EnemyBase.h"


class NaporeonFish :public EnemyBase {
public:
	NaporeonFish(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2, bool no_move = false);
	~NaporeonFish()override {}

	void Update()override;
	void Draw()override;
	StateId StateChangeCheck()override;

private:
	int m_change_direction_count_timer;
	int m_change_direction_time;
};
/*
Stateで徘徊Stateを作る
sinカーブ？とかを使って特定の位置を移動する挙動にする
Idも新しくPatrolIdとかを作ってほら貝とは別でメガネ用の横移動に
遷移するときに画像を反転するように
プレイヤーが近づいたら追跡処理に移行


*/