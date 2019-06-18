#pragma once

#include"../EnemyStateBase.h"


class Patrol :public StateBase {
public:
	static Patrol* GetInstance();
	void Action(EnemyBase* e)override;
private:
	Patrol() {
		//m_posx_count = 0;
	}
	~Patrol() {}

private:
	
};