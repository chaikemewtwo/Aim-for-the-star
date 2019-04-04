#pragma once
#include "../PlayerStateBase.h"


// 泳ぎ状態
class SwimState : public PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;
};
