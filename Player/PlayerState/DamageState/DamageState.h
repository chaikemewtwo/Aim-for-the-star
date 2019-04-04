#pragma once
#include "../PlayerStateBase.h"


// 被弾状態
class DamageState : public PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;
};
