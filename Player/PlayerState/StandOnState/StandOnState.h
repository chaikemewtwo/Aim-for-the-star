#pragma once
#include "../PlayerStateBase.h"


// 立ち状態（オブジェクト上など）
class StandOnState : public PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;

};
