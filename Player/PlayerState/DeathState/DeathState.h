#pragma once
#include "../PlayerStateBase.h"


// 死亡状態
class DeathState : public PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Init(PlayerBase* p) override;

};
