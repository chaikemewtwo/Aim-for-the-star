#pragma once
#include"StateBaseh.h"

// 縦移動クラス
class VerticalMove :public StateBase {
public:
	static VerticalMove *GetInstance();
	void Action()override;
private:
	VerticalMove() {}
};
