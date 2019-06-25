#include"EnemyVerticalMoveState.h"
#include"../../Enemy/EnemyBase.h"


VerticalMove* VerticalMove::GetInstance() {

	static VerticalMove s_vertical_move;
	return &s_vertical_move;
}
//――――――――――――――――――――――――

void VerticalMove::Action(EnemyBase* e) {

	e->VerticalMove();
}
//――――――――――――――――――――――――
