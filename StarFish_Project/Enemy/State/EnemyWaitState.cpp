#include"EnemyWaitState.h"
#include"../Enemy/SeaUrchin.h"

Wait *Wait::GetInstance() {
	static Wait s_wait;
	return &s_wait;
}
//―――――――――――――――――――――

// 待機　　基本はここから各Stateに遷移
void Wait::Action(EnemyBase* e) {
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
