#pragma once
#include "../PlayerStateBase.h"


// 待機状態(オブジェクト上以外、オブジェクト上での待機状態はStandingWaitStateクラス)
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
	// HACK:奇数じゃないと止まる
	const int ONE_ANIMATION_SPEED = 7;

	// 統合画像内の画像枚数
	const int MAX_TEXTURE_NUM = 6;
};
