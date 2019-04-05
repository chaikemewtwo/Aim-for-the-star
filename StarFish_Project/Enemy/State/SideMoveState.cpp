#include"SideMoveState.h"

SideMove* SideMove::GetInstance() {
	static SideMove s_side_move;
	return &s_side_move;
}

void SideMove::Action() {
	// 横に直線移動する処理
}
