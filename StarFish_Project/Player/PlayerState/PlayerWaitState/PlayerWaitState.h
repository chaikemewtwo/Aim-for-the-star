#pragma once
#include "../PlayerStateBase.h"


// 待機状態
// オブジェクト上での待機状態はStandingWaitStateクラスです
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
	// 1アニメーションの速さ
	// この速さで1アニメーションが進んでいく
	static const int ONE_ANIMATION_SPEED;

	// 統合画像内のアニメーション枚数
	// 1つの統合画像にキャラの画像が詰め込んであるか
	static const int MAX_ANIMATION_TEX_NUM;
};
