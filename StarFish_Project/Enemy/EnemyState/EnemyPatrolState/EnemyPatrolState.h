#pragma once

#include"EnemyPatrolBase.h"
#include"../EnemyStateBase.h"


class Patrol :public PatrolBase {
public:
	static Patrol* GetInstance();
	void Action(EnemyBase* e)override;

private:
	Patrol() {}
	~Patrol() {}
};