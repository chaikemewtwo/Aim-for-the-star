#pragma once
#include "../PlayerStateBase.h"


// 被弾状態
// HACK:被弾状態は不要な可能性がある
class PlayerDamageState : public PlayerStateBase {
public:
	void Init(PlayerBase * p) override;
	void Update(PlayerBase * p) override;
private:
	int count;
	// 数値は仮のもの
	const int MAX_COUNT = 120;

	// 数値は仮のもの、統合画像が完成次第変更する
	const int MAX_TEXTURE_NUM = 8;
};
