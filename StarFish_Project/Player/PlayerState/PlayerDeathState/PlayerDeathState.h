#pragma once
#include "../PlayerStateBase.h"


// 死亡状態
class PlayerDeathState : public PlayerStateBase {
public:
	// インスタンス取得
	static PlayerDeathState *GetInstance()
	{
		static PlayerDeathState instance;
		return &instance;
	}

	void Init(Player* p) override;
	void Update(Player* p) override;
private:
	// 1アニメーションの速さ
	// この速さで1アニメーションが進んでいく
	static const int ONE_ANIMATION_SPEED;

	// 統合画像内のアニメーション枚数
	// 1つの統合画像にキャラの画像が詰め込んであるか
	static const int MAX_ANIMATION_TEX_NUM;

	// 1周目以外の初期アニメーションカウント
	// 死亡状態のみ2周目からはアニメーションの途中から再生するため
	static const int ANIMATION_INIT_COUNT;
};
