#include"EnemySideMoveState.h"
#include"../Enemy/EnemyBase.h"

SideMove* SideMove::GetInstance() {
	static SideMove s_side_move;
	return &s_side_move;
}
//――――――――――――――――――――――

void SideMove::Action(EnemyBase* e) {
	e->SetStateId(SideMoveId);
	// 横に直線移動する処理
	int x;
	if (e->IsLeft() == true) {
		x = e->GetPosX() + e->GetSpeed();
		e->SetPosX(x);
	}
	else if (e->IsLeft() == false) {
		x = e->GetPosX() - e->GetSpeed();
		e->SetPosX(x);
	}
}
//――――――――――――――――――――――
