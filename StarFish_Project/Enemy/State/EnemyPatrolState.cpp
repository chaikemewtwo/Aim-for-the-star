#include<math.h>
#include"EnemyPatrolState.h"
#include"EnemyWaitState.h"
#include"EnemyChaseState.h"
#include"../Enemy/EnemyBase.h"


Patrol* Patrol::GetInstance() {
	static Patrol s_patrol;
	return &s_patrol;
}

void Patrol::Action(EnemyBase* e) {

	D3DXVECTOR2 pos = e->GetPos();

	pos.x -= e->CalcSinCurve();
	
	e->SetPos(pos);

	if (e->StateChangeCheck() == StateId::CHASE_ID) {
		e->ChangeState(Chase::GetInstance());
	}
	else {
		e->ChangeState(Wait::GetInstance());
	}
}