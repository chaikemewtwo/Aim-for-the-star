﻿#pragma once
#include "../Player/Player.h"


class StaminaUI:public Object {
public:
	StaminaUI(Player* p1, Player* p2);

	void Update()override;
	void Draw()override;

private:
	// プレイヤーのスタミナの最大値を100%としたスタミナの割合
	float StaminaParcentage(Player* p);

	// ゲージのY座標算出
	float GagePosYCalc(float stamina_parcent);

	// ゲージ満タン時の座標
	const float GAGE_MAX_POS = 380.f;

	// ゲージがなくなった時の座標
	const float GAGE_UNDER_POS = 1000.f;

	// ゲージの量
	const float ALL_GAGE = GAGE_UNDER_POS - GAGE_MAX_POS;

	// 自機1
	Player * p1;
	// 自機2
	Player * p2;

	// 自機1のスタミナの割合
	float p1_stamina_parcent;
	// 自機2のスタミナの割合
	float p2_stamina_parcent;

	// テスト用
	float y;
};
