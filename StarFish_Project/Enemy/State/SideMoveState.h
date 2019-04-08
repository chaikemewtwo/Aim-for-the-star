#pragma once
#include"StateBase.h"

// 横移動クラス
class SideMove :public StateBase {
public:
	static SideMove *GetInstance();
	void Action()override;
private:
	SideMove() {}
};
