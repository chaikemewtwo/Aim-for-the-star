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

	// 受け取ったプレイヤーの座標でラジアンを計算
	D3DXVECTOR2 target = e->GetTargetPos();
	float radian = atan2((target.y - e->GetPos().y), (target.x - e->GetPos().x));
	
	D3DXVECTOR2 pos;
	// ラジアンからプレイヤーに向かっての移動を計算
	pos.x = e->GetPos().x + cosf(radian) * e->GetSpeed();
	pos.y = e->GetPos().y + sinf(radian) * e->GetSpeed();

	e->SetPos(pos);
	
	if (e->CheckChangeState() != StateId::CHASE_ID) {
		e->ChangeState(Wait::GetInstance());
	}
}
