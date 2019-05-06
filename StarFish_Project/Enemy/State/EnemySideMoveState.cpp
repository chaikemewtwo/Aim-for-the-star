#include"EnemySideMoveState.h"
#include"../Enemy/EnemyBase.h"

SideMove* SideMove::GetInstance() {
	static SideMove s_side_move;
	return &s_side_move;
}
//――――――――――――――――――――――

// 横に直線移動する処理
void SideMove::Action(EnemyBase* e) {
	e->SetStateId(SideMoveId);

	// 画面の左側にいたら、右に向かって移動
	D3DXVECTOR2 pos;
	if (e->IsLeft() == true) {
		pos = e->GetPos();
		pos.x += e->GetSpeed();
		e->SetPos(pos);
	}
	// 画面の右側にいたら、左に向かって移動
	else if (e->IsLeft() == false) {
		pos = e->GetPos();
		pos.x -= e->GetSpeed();
		e->SetPos(pos);
	}
}
//――――――――――――――――――――――
