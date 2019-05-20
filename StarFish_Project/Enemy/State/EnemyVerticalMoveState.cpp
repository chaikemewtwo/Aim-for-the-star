#include"EnemyVerticalMoveState.h"

VerticalMove *VerticalMove::GetInstance() {
	static VerticalMove s_vertical_move;
	return &s_vertical_move;
}
//――――――――――――――――――――――――

// 縦の直線移動
void VerticalMove::Action(EnemyBase* e) {
	D3DXVECTOR2 pos = e->GetPos();
	pos.y += e->GetSpeed();
	e->SetPos(pos);
}
//――――――――――――――――――――――――
