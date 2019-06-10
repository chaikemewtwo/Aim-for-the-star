#include"EnemyWaitState.h"
#include"EnemySideMoveState.h"
#include"EnemyVerticalMoveState.h"
#include"../Enemy/EnemyBase.h"


Wait *Wait::GetInstance() {

	static Wait s_wait;
	return &s_wait;
}
//―――――――――――――――――――――

void Wait::Action(EnemyBase* e) {

	// 返ってきたStateIdによって遷移先を変える
	if (e->StateChangeCheck() == WAIT_ID) {
		return;
	}
	else if (e->StateChangeCheck() == SIDEMOVE_ID) {
		e->ChangeState(SideMove::GetInstance());
	}
	else if (e->StateChangeCheck() == VERTICALMOVE_ID) {
		e->ChangeState(VerticalMove::GetInstance());
	}
	else if (e->StateChangeCheck() == CHASE_ID) {
		
	}
}
//―――――――――――――――――――――
