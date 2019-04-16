#pragma once
#include "../PlayerStateBase.h"
#include "../WaitState/WaitState.h"


// 泳ぎ状態
class SwimState : public PlayerStateBase {
public:
	void Init(PlayerBase* p) override;
	void Update(PlayerBase* p) override;

private:
	int count;
	const int MAX_COUNT = 120;
};
