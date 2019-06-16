#pragma once

#include"EnemyStateBase.h"


class Patrol :public StateBase {
public:
	static Patrol* GetInstance();
	void Action(EnemyBase* e)override;
private:
	Patrol() {}
	~Patrol() {}

private:
	float m_posx_count;
	const float m_max_posx_count = 50;
};