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
	if (e->CheckChangeState() == StateId::WAIT_ID) {
		return;
	}
	else if (e->CheckChangeState() == StateId::SIDEMOVE_ID) {
		e->ChangeState(SideMove::GetInstance());
	}
	else if (e->CheckChangeState() == StateId::VERTICALMOVE_ID) {
		e->ChangeState(VerticalMove::GetInstance());
	}
	else if (e->CheckChangeState() == PATROL_ID) {
		e->ChangeState(Patrol::GetInstance());
	}
}
//―――――――――――――――――――――
