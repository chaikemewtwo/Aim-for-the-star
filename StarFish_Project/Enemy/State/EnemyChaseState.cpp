#include"EnemyChaseState.h"


Chase* Chase::GetInstance() {
	static Chase s_chase;
	return &s_chase;
}
//――――――――――――――――――

void Chase::Action(EnemyBase* e) {

	
}
