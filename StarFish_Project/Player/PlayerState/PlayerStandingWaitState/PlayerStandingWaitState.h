#pragma once
#include "../PlayerStateBase.h"


// 立ち待機状態（オブジェクト上など）
class PlayerStandingWaitState : public PlayerStateBase {
public:
	// インスタンス取得
	static PlayerStandingWaitState *GetInstance()
	{
		static PlayerStandingWaitState instance;
		return &instance;
	}

	void Init(PlayerBase* p) override;
	void Update(PlayerBase* p) override;

private:
	int count;
	// 数値は仮のもの
	const int MAX_COUNT = 120;

	const int MAX_TEXTURE_NUM = 8;
};
