#include"EnemyPatrolState.h"
#include"../EnemyWaitState/EnemyWaitState.h"
#include"../../Enemy/EnemyBase.h"


Patrol* Patrol::GetInstance() {
	static Patrol s_patrol;
	return &s_patrol;
}
//――――――――――――――――――

void Patrol::Action(EnemyBase* e) {
	
	e->Patrol();

	if (e->CheckChangeState() != StateId::PATROL_ID) {
		e->ChangeState(Wait::GetInstance());
	}
}
//――――――――――――――――――
