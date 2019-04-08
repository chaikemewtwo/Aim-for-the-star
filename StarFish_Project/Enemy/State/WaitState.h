#pragma once
#include"StateBase.h"

// 待機クラス
class Wait :public StateBase {
public:
	static Wait *GetInstance();
	void Action()override;
private:
	Wait() {}
};
