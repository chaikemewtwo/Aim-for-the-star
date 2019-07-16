#pragma once

#include"../EnemyStateBase.h"


// 徘徊移動クラス
class Patrol :public StateBase {
public:
	// シングルトン
	static Patrol* GetInstance();

	void Action(EnemyBase* e)override;

private:
	Patrol() {}
	~Patrol() {}
};