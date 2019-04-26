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
	int count;
	const int MAX_COUNT = 120;
};
