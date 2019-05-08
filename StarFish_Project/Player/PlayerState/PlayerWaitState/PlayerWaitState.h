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
	// アニメーション1枚を何Fやるか
	const int ONE_ANIMATION_SPEED = 8;

	// アニメーションの画像枚数
	const int MAX_ANIMATION_TEX_NUM = 6;
};
