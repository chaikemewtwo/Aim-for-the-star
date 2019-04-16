#pragma once
#include "../PlayerStateBase.h"


// 立ち待機状態（オブジェクト上など）
class StandingWaitState : public PlayerStateBase {
public:
	void Init(PlayerBase* p) override;
	void Update(PlayerBase* p) override;
	
};
