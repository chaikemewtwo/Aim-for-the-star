#pragma once

#include"../EnemyStateBase.h"


// 追跡クラス
class Chase :public StateBase {
public:
	// シングルトン
	static Chase* GetInstance();

	void Action(EnemyBase* e)override;

private:
	Chase() {}
	~Chase() {}
};