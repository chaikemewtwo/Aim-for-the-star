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

	// 初期化
	void Init(Player* p) override;
	// 更新
	void Update(Player* p) override;

private:
	// 1アニメーションの速さ
	const int ONE_ANIMATION_SPEED = 6;

	// 統合画像内の画像枚数
	const int MAX_ANIMATION_TEX_NUM = 16;

	// 状態切り替えカウント
	const int CHANGE_STATE_COUNT = ONE_ANIMATION_SPEED * MAX_ANIMATION_TEX_NUM;
};
