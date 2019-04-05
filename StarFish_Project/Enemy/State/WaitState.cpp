#include"WaitState.h"

Wait *Wait::GetInstance() {
	static Wait s_wait;
	return &s_wait;
}

void Wait::Action() {
	// 待機処理
}
