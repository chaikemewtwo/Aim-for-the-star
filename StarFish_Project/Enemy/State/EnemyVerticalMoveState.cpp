#include"EnemyVerticalMoveState.h"

VerticalMove *VerticalMove::GetInstance() {
	static VerticalMove s_vertical_move;
	return &s_vertical_move;
}
//――――――――――――――――――――――――

// 縦の直線移動
void VerticalMove::Action(EnemyBase* e) {
	e->SetStateId(VerticalMoveId);
	float y = e->GetPosY() + e->GetSpeed();
	e->SetPosY(y);
}
//――――――――――――――――――――――――
