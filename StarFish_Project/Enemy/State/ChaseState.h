#pragma once
#include"StateBaseh.h"

// 追跡クラス
class Chase :public StateBase {
public:
	static Chase *GetInstance();
	void Action()override;
private:
	Chase() {}
};
