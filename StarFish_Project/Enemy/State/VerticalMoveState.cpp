#include"VerticalMoveState.h"

VerticalMove *VerticalMove::GetInstance() {
	static VerticalMove s_vertical_move;
	return &s_vertical_move;
}

void VerticalMove::Action() {
	// 縦の直進移動処理
}
