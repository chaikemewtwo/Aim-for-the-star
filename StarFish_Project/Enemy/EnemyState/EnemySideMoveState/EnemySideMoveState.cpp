#include"EnemySideMoveState.h"
#include"../../Enemy/EnemyBase.h"


SideMove* SideMove::GetInstance() {

	static SideMove s_side_move;
	return &s_side_move;
}
//――――――――――――――――――――――

// 横に直線移動する処理
void SideMove::Action(EnemyBase* e) {
	
	D3DXVECTOR2 pos;
	pos = e->GetPos();

	// 画面の左側にいたら、右に向かって移動
	if (e->IsLeft() == true) {
		pos.x += e->GetSpeed();
	}
	// 画面の右側にいたら、左に向かって移動
	else if (e->IsLeft() == false) {
		pos.x -= e->GetSpeed();
	}

	e->SetPos(pos);
}
//――――――――――――――――――――――
