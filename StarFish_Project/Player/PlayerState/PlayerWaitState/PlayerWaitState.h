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

	void Init(Player* p) override;
	void Update(Player* p)  override;

private:
	// アニメーション1枚を何Fやるか
	const int ONE_ANIMATION_SPEED = 8;

	// アニメーションの画像枚数
	const int MAX_ANIMATION_TEX_NUM = 6;

	// 泳ぎ状態へ移行する際に消費するスタミナ
	const int TO_SWIM_NEEDED_STAMINA = 100;
};
