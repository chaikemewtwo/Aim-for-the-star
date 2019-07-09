#pragma once

#include"../EnemyStateBase.h"


// 待機クラス
class Wait :public StateBase {
public:
	// シングルトン
	static Wait* GetInstance();

	void Action(EnemyBase* e)override;

private:
	Wait() {}
	~Wait() {}
};
