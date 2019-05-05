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

	void Update(PlayerBase* p) override;
	void Init(PlayerBase* p) override;

private:
	// 数値は仮のもの、統合画像が完成次第変更する
	const int MAX_TEXTURE_NUM = 8;
};
