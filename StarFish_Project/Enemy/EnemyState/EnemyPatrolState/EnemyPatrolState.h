#pragma once

#include"../EnemyStateBase.h"


class Patrol :public StateBase {
public:
	// シングルトン
	static Patrol* GetInstance();

	void Action(EnemyBase* e)override;

private:
	Patrol() {}
	~Patrol() {}
};