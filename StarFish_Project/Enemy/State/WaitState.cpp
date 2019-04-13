#include"WaitState.h"
#include"../Enemy/SeaUrchin.h"

Wait *Wait::GetInstance() {
	static Wait s_wait;
	return &s_wait;
}

void Wait::Action(EnemyBase* e) {
	e->SetChangeTimer();
}
