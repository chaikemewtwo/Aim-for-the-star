#pragma once
#include"StateBase.h"
#include"../Enemy/SeaUrchin.h"

// 縦移動クラス
class VerticalMove :public StateBase {
public:
	// シングルトン
	static VerticalMove *GetInstance();
	void Action(EnemyBase* e)override;
private:
	VerticalMove() {}
	~VerticalMove() {}
};
