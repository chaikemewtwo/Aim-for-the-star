#include<math.h>
#include"EnemyPatrolState.h"
#include"../EnemyWaitState/EnemyWaitState.h"
#include"../EnemyChaseState/EnemyChaseState.h"
#include"../../Enemy/EnemyBase.h"


Patrol* Patrol::GetInstance() {
	static Patrol s_patrol;
	return &s_patrol;
}

void Patrol::Action(EnemyBase* e) {

	D3DXVECTOR2 pos = e->GetPos();

	pos.x -= e->CalcSinCurve();
	
	e->SetPos(pos);

	if (e->CheckChangeState() == StateId::CHASE_ID) {
		e->ChangeState(Chase::GetInstance());
	}
	else {
		e->ChangeState(Wait::GetInstance());
	}
}