#pragma once
#include "../PlayerStateBase.h"
#include "../SwimState/SwimState.h"


// 待機状態(落下)
class WaitState : public PlayerStateBase {
public:
	void Init(PlayerBase* p) override;
	void Update(PlayerBase* p) override;
	
};
