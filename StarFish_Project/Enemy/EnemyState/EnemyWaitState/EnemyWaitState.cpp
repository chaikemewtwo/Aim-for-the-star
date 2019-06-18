#include"EnemyWaitState.h"
#include"../EnemySideMoveState/EnemySideMoveState.h"
#include"../EnemyVerticalMoveState/EnemyVerticalMoveState.h"
#include"../EnemyPatrolState/EnemyPatrolState.h"
#include"../../Enemy/EnemyBase.h"


Wait* Wait::GetInstance() {

	static Wait s_wait;
	return &s_wait;
}
//―――――――――――――――――――――

void Wait::Action(EnemyBase* e) {

	// 返ってきたStateIdによって遷移先を変える
	if (e->StateChangeCheck() == StateId::WAIT_ID) {
		return;
	}
	else if (e->StateChangeCheck() == StateId::SIDEMOVE_ID) {
		e->ChangeState(SideMove::GetInstance());
	}
	else if (e->StateChangeCheck() == StateId::VERTICALMOVE_ID) {
		e->ChangeState(VerticalMove::GetInstance());
	}
	else if (e->StateChangeCheck() == PATROL_ID) {
		e->ChangeState(Patrol::GetInstance());
	}
}
//―――――――――――――――――――――
