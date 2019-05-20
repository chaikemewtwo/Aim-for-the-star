#include"EnemyWaitState.h"
#include"EnemySideMoveState.h"
#include"EnemyVerticalMoveState.h"
#include"../Enemy/SeaUrchin.h"

Wait *Wait::GetInstance() {
	static Wait s_wait;
	return &s_wait;
}
//―――――――――――――――――――――

// 待機　　基本はここから各Stateに遷移
void Wait::Action(EnemyBase* e) {
	if (e->StateChangeCheck() == WAIT_ID) {
		return;
	}
	else if (e->StateChangeCheck() == SIDEMOVE_ID) {
		e->ChangeState(SideMove::GetInstance());
	}
	else if (e->StateChangeCheck() == VERTICALMOVE_ID) {
		e->ChangeState(VerticalMove::GetInstance());
	}
}
//―――――――――――――――――――――
