#include"ChaseState.h"

Chase *Chase::GetInstance() {
	static Chase s_chase;
	return &s_chase;
}

void Chase::Action() {
	// 追跡処理
}
