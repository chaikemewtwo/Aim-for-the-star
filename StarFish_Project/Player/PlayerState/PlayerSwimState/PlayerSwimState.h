#pragma once
#include "../PlayerStateBase.h"
#include "../PlayerWaitState/PlayerWaitState.h"


// 泳ぎ状態
class PlayerSwimState : public PlayerStateBase {
public:
	// インスタンス取得
	static PlayerSwimState *GetInstance()
	{
		static PlayerSwimState instance;
		return &instance;
	}

	void Init(Player* p) override;
	void Update(Player* p) override;

private:
	const int ONE_ANIMATION_SPEED = 8;

	const int MAX_ANIMATION_TEX_NUM = 16;

	const int MAX_COUNT = ONE_ANIMATION_SPEED * MAX_ANIMATION_TEX_NUM;
};
