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

	void Init(Player* p) override;
	void Update(Player* p) override;

private:
	// 1アニメーションの速さ
	const int ONE_ANIMATION_SPEED = 7;

	// 統合画像内の画像枚数
	const int MAX_ANIMATION_TEX_NUM = 7;

	// 状態切り替えカウント
	const int CHANGE_STATE_COUNT = ONE_ANIMATION_SPEED * MAX_ANIMATION_TEX_NUM;
};
