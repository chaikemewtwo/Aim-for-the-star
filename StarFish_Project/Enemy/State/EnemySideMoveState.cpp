#include"EnemySideMoveState.h"

SideMove* SideMove::GetInstance() {
	static SideMove s_side_move;
	return &s_side_move;
}
//――――――――――――――――――――――

void SideMove::Action(EnemyBase* e) {
	// 横に直線移動する処理
}
//――――――――――――――――――――――
