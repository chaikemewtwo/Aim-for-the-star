#pragma once
#include "PlayerStateBase.h"
#include "PlayerWaitState\PlayerWaitState.h"
#include "PlayerSwimState\PlayerSwimState.h"
#include "PlayerStandingWaitState\PlayerStandingWaitState.h"
#include "PlayerDamageState\PlayerDamageState.h"
#include "PlayerDeathState\PlayerDeathState.h"

class PlayerManager {
public:
	void Update();

private:
	// ステートベースインスタンス
	PlayerStateBase * m_state;
};