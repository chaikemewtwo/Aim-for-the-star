#pragma once
#include "../Player/Player.h"


class GameUI:public Object {
public:
	GameUI(Player* p1, Player* p2);

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

	// 右ゲージの位置
	const float RIGHT_GAGE_POS = Window::WIDTH - 132.f;
	// 右岩の位置
	const float RIGHT_ROCK_POS = Window::WIDTH - 196.f;

	// 自機1
	Player * p1;
	// 自機2
	Player * p2;
};
