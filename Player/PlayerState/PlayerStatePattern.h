#pragma once
#include "../PlayerState/PlayerState.h"

class PlayerStatePattern {
public:
	PlayerStatePattern();

	void Update();
	void Draw();
private:
	void ChangeState();

	PlayerStateBase* state;
};
