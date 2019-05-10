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
	// 数値は仮のもの
	const int ONE_ANIMATION_SPEED = 10;

	// 数値は仮のもの、統合画像が完成次第変更する
	const int MAX_ANIMATION_TEX_NUM = 8;
};
