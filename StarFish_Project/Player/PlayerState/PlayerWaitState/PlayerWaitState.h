#pragma once
#include "../PlayerStateBase.h"


// 待機状態(落下)
class PlayerWaitState : public PlayerStateBase {
public:
	// インスタンス取得
	static PlayerWaitState *GetInstance()
	{
		static PlayerWaitState instance;
		return &instance;
	}

	void Init(PlayerBase* p) override;
	void Update(PlayerBase* p)  override;

private:
	PlayerWaitState() {}

	// 数値は仮のもの
	const int MAX_COUNT = 80;

	const float ONE_ANIMATION_SPEED = 25;

	const int MAX_TEXTURE_NUM = 6;
	
};
