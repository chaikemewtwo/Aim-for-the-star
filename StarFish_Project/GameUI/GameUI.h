#pragma once
#include "../Player/PlayerManager.h"


class GameUI:public Object {
public:
	GameUI(PlayerManager* pm);

	void Update()override;
	void Draw()override;

private:
	// 両自機のスタミナゲージの色変更
	// プレイヤーのスタミナが一定以下になると赤に変わる
	void GageColorChange();

	// スタミナゲージのY座標算出
	// プレイヤーのスタミナの増減をゲージに反映
	float GagePosYCalc(float stamina_parcent);

private:
	// ゲージ満タン時のY座標
	static const float GAGE_MAX_POS_Y;

	// ゲージがなくなった時のY座標
	static const float GAGE_UNDER_POS_Y;

	// ゲージの全体量
	static const float ALL_GAGE;

	// GageColorChange()でゲージの量の変えるスタミナの割合
	static const float DANGER_LINE_PARCENTAGE;

	// 自機2のスタミナゲージのX座標
	static const float RIGHT_GAGE_POS_X;

	// 自機2のゲージ枠の岩のX座標
	static const float RIGHT_ROCK_POS_X;

private:
	PlayerManager * m_p_player_manager; //プレイヤーマネージャー
	std::string m_1p_gage_texture;		// 自機1のスタミナゲージ画像
	std::string m_2p_gage_texture;		// 自機2のスタミナゲージ画像
};
