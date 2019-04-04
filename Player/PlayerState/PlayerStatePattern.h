#pragma once
#include "../PlayerState/PlayerStateBase.h"


// MEMO:プレイヤーベースと未統合
class PlayerStatePattern {
public:
	PlayerStatePattern();

	void Update();
	void Draw();

private:
	void ChangeState(PlayerStateBase* state);

	PlayerStateBase* state;
};
