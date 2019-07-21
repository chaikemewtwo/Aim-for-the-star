#include"EnemyPatrolState.h"
#include"../EnemyWaitState/EnemyWaitState.h"
#include"../../Enemy/EnemyBase.h"


Patrol* Patrol::GetInstance() {
	static Patrol s_patrol;
	return &s_patrol;
}
//――――――――――――――――――

// 一定の場所を徘徊する挙動
void Patrol::Action(EnemyBase* e) {
	
	e->Patrol();

	if (e->CheckChangeState() != StateId::PATROL_ID) {
		e->ChangeState(Wait::GetInstance());
	}
}
//――――――――――――――――――
