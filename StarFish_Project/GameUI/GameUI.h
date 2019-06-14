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

	// ゲージ満タン時のY座標
	const float GAGE_MAX_POS_Y = 380.f;

	// ゲージがなくなった時のY座標
	const float GAGE_UNDER_POS_Y = 1000.f;

	// ゲージの量
	const float ALL_GAGE = GAGE_UNDER_POS_Y - GAGE_MAX_POS_Y;

	// 右ゲージの位置
	const float RIGHT_GAGE_POS = Window::WIDTH - 132.f;
	// 右岩の位置
	const float RIGHT_ROCK_POS = Window::WIDTH - 196.f;

	// 自機1
	Player * p1;
	// 自機2
	Player * p2;

	// ゲージの画像指定用定数
	enum GAGE_TEXTURE_INDEX {
		ORANGE_GAGE,
		PINK_GAGE,
		RED_GAGE,
		MAX_NUM
	};

	std::string gage_textue[MAX_NUM];
};
