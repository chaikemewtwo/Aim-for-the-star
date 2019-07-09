#pragma once

#include"../EnemyStateBase.h"


// 横移動クラス
class SideMove :public StateBase {
public:
	// シングルトン
	static SideMove* GetInstance();

	void Action(EnemyBase* e)override;

private:
	SideMove() {}
	~SideMove() {}
};
