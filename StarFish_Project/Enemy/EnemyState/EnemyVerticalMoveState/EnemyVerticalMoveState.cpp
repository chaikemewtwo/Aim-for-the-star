#include"EnemyVerticalMoveState.h"
#include"../../Enemy/EnemyBase.h"


VerticalMove* VerticalMove::GetInstance() {

	static VerticalMove s_vertical_move;
	return &s_vertical_move;
}
//――――――――――――――――――――――――

// 縦に直線移動する挙動
void VerticalMove::Action(EnemyBase* e) {

	e->VerticalMove();
}
//――――――――――――――――――――――――
