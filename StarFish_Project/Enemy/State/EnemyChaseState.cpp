#include<math.h>
#include"EnemyChaseState.h"
#include"EnemyWaitState.h"
#include"../Enemy/EnemyBase.h"


Chase* Chase::GetInstance() {
	static Chase s_chase;
	return &s_chase;
}
//――――――――――――――――――

void Chase::Action(EnemyBase* e) {

	D3DXVECTOR2 target = e->CheckCloseTarget();
	float radian = atan2((target.y - e->GetPos().y), (target.x - e->GetPos().x));
	D3DXVECTOR2 pos;
	pos.x = e->GetPos().x + cosf(radian) * e->GetSpeed();
	pos.y = e->GetPos().y + sinf(radian) * e->GetSpeed();

	e->SetPos(pos);
	
	if (e->StateChangeCheck() != StateId::CHASE_ID) {
		e->ChangeState(Wait::GetInstance());
	}
}
