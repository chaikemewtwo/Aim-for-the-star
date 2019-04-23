#pragma once
#include "../PlayerStateBase.h"
#include "../PlayerSwimState/PlayerSwimState.h"


// 待機状態(落下)
class PlayerWaitState : public PlayerStateBase {
public:
	void Init(PlayerBase* p) override;
	void Update(PlayerBase* p) override;

private:
	const int MAX_TEXTURE_NUM = 8;
	
};
