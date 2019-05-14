#pragma once
#include "../Player/Player.h"


class StaminaUI:public Object {
public:
	StaminaUI(Player* p1, Player* p2);

	void Update()override;
	void Draw()override;

private:
	// スタミナの最大値を100%としたスタミナの割合
	float stamina_parcentage(Player* p);

	// ゲージ満タン時の座標
	const int GAGE_MAX_POS = 380;

	// ゲージがなくなった時の座標
	const int GAGE_UNDER_POS = 1000;

	// ゲージの量
	const int ALL_GAGE = GAGE_UNDER_POS - GAGE_MAX_POS;

	// 自機1
	Player * p1;
	// 自機2
	Player * p2;

	int test;

	// テスト用
	float y;
};
