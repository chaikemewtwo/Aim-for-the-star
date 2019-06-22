#include<math.h>
#include"EnemyPatrolState.h"
#include"../EnemyWaitState/EnemyWaitState.h"
#include"../EnemyChaseState/EnemyChaseState.h"
#include"../../Enemy/EnemyBase.h"


Patrol* Patrol::GetInstance() {
	static Patrol s_patrol;
	return &s_patrol;
}
//――――――――――――――――――

void Patrol::Action(EnemyBase* e) {
	
	PatrolBase::Action(e);

	if (e->CheckChangeState() != StateId::PATROL_ID) {
		e->ChangeState(Wait::GetInstance());
	}
}
//――――――――――――――――――
