#pragma once
#include "../PlayerStateBase.h"


// 被弾状態
// HACK:被弾状態は不要な可能性がある
class PlayerDamageState : public PlayerStateBase {
public:
	void Init(PlayerBase * p) override;
	void Update(PlayerBase * p) override;
	
};
