#pragma once
#include "../PlayerStateBase.h"


// 死亡状態
class PlayerDeathState : public PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Init(PlayerBase* p) override;

};
