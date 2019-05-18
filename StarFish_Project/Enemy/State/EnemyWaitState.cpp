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
	e->SetStateId(WAIT_ID);

	// NoMoveがtrueならStateは遷移させない
	if (e->NoMove() == true) {
		return;
	}

	// EnemyTypeで遷移先を変更
	switch (e->GetEnemyType()) {
	case SEAURCHIN_ID:
		e->ChangeState(VerticalMove::GetInstance());
		break;
	case SELLFISH_ID:
		if (e->PosIsTop() == true && 256 > e->CalcDistance()) {
			e->ChangeState(SideMove::GetInstance());
		}
		else if(e->PosIsTop() == false && 128 > e->CalcDistance()) {
			e->ChangeState(SideMove::GetInstance());
		}
		break;
	case NAPOLEONFISH_ID:
		// 仮でSideMoveに遷移
		e->ChangeState(SideMove::GetInstance());
		break;
	}
}
//―――――――――――――――――――――
