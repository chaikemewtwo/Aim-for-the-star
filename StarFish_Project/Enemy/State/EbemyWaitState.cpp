#include"EnemyWaitState.h"
#include"../Enemy/SeaUrchin.h"

Wait *Wait::GetInstance() {
	static Wait s_wait;
	return &s_wait;
}

void Wait::Action(EnemyBase* e) {
	switch (e->GetEnemyType()) {
	case SeaUrchinId:
		e->ChangeState(VerticalMove::GetInstance());
		break;
	case SellFishId:
		e->ChangeState(SideMove::GetInstance());
		break;
	case NapoleonFishId:
		e->ChangeState(SideMove::GetInstance());
		break;
	}
}
