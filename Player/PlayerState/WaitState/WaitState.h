#pragma once
#include "../PlayerStateBase.h"


// 待機状態(落下)
class WaitState : public PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;
};
