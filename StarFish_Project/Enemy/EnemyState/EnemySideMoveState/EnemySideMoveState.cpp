#include"EnemySideMoveState.h"
#include"../../Enemy/EnemyBase.h"


SideMove* SideMove::GetInstance() {

	static SideMove s_side_move;
	return &s_side_move;
}
//――――――――――――――――――――――

// 横に直線移動する処理
void SideMove::Action(EnemyBase* e) {

	e->SideMove();
}
//――――――――――――――――――――――
