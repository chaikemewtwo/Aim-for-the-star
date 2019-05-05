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

	void Init(PlayerBase* p) override;
	void Update(PlayerBase* p) override;

private:
	// HACK:奇数じゃないと止まる
	const int ONE_ANIMATION_SPEED = 7;

	const int MAX_TEXTURE_NUM = 16;

	// 数値は仮のもの
	const int MAX_COUNT = ONE_ANIMATION_SPEED * MAX_TEXTURE_NUM;
};
