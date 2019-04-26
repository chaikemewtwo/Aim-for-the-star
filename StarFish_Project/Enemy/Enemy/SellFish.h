#pragma once

#include"EnemyBase.h"
#include"../../Lib/Window/Window.h"

class SellFish :public EnemyBase {
public:
	SellFish(float x, float y, bool no_move = false);
	~SellFish() {}
	void Init()override;
	void Update()override;
	void Draw()override;
	void ChangeState(StateBase* state)override;
private:
	StateBase* m_pstate_base;
};
