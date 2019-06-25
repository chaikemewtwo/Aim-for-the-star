#include<math.h>
#include"EnemyChaseState.h"
#include"../EnemyWaitState/EnemyWaitState.h"
#include"../../Enemy/EnemyBase.h"


Chase* Chase::GetInstance() {
	static Chase s_chase;
	return &s_chase;
}
//――――――――――――――――――

void Chase::Action(EnemyBase* e) {

	e->Chase();
	
	if (e->CheckChangeState() != StateId::CHASE_ID) {
		e->ChangeState(Wait::GetInstance());
	}
}
//――――――――――――――――――
