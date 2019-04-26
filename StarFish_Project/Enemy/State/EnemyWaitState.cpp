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
	// NoMoveがtrueならStateは遷移させない
	if (e->NoMove() == true) {
		return;
	}

	// EnemyTypeで遷移先を変更
	switch (e->GetEnemyType()) {
	case SeaUrchinId:
		e->ChangeState(VerticalMove::GetInstance());
		break;
	case SellFishId:
		e->ChangeState(SideMove::GetInstance());
		break;
	case NapoleonFishId:
		// 仮でSideMoveに遷移
		e->ChangeState(SideMove::GetInstance());
		break;
	}
}
//―――――――――――――――――――――
