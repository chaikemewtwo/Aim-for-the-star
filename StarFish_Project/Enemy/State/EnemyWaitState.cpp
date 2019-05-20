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
	/*
	// NoMoveがtrueならStateは遷移させない
	if (e->NoMove() == true) {
		return;
	}*/

	e->SetStateId(WAIT_ID);
	 if (e->IsStateChangeCheck() == ATTACK_READY_ID) {
		e->SetStateId(ATTACK_READY_ID);
	}
	else if (e->IsStateChangeCheck() == SIDEMOVE_ID) {
		 e->SetStateId(SIDEMOVE_ID);
		e->ChangeState(SideMove::GetInstance());
	}
}
//―――――――――――――――――――――
