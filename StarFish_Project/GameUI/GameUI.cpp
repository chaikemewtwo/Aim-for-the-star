#include "GameUI.h"
#include "../Lib/Sound/DirectSound.h"


const float GameUI::GAGE_MAX_POS_Y = 380.f;
const float GameUI::GAGE_UNDER_POS_Y = 1000.f;
const float GameUI::ALL_GAGE = GAGE_UNDER_POS_Y - GAGE_MAX_POS_Y;
const float GameUI::RIGHT_GAGE_POS_X = Window::WIDTH - 132.f;
const float GameUI::RIGHT_ROCK_POS_X = Window::WIDTH - 196.f;
const float GameUI::DANGER_LINE_PARCENTAGE = 0.3f;


GameUI::GameUI(PlayerManager* pm) {
	m_p_player_manager = pm;
	m_sort_object_type = SortObjectType::GAME_UI;
	
	m_1p_gage_texture = "Resource/Texture/UI/ui_orange.png";
	m_2p_gage_texture = "Resource/Texture/UI/ui_violet.png";
}


void GameUI::Update(){
	GageColorChange();
}


void GameUI::Draw() {
	// 左右黒バー
	// スタミナゲージの奥に背景が描画されるのを防止するため
	Texture::Draw2D("Resource/Texture/UI/ui_black.png", 0.f, GAGE_MAX_POS_Y);
	Texture::Draw2D("Resource/Texture/UI/ui_black.png", RIGHT_GAGE_POS_X, GAGE_MAX_POS_Y);

	// スタミナゲージ
	// どちらかの自機のスタミナがなくなるとスタミナゲージの描画をしない
	if (m_p_player_manager->IsActiveRelay(Player::STAR_1) == true&& m_p_player_manager->IsActiveRelay(Player::STAR_2) == true) {
		// 自機1スタミナゲージ
		Texture::Draw2D(m_1p_gage_texture.c_str(), 0.f, GagePosYCalc(m_p_player_manager->StaminaParcentageRelay(Player::STAR_1)));

		// 自機2スタミナゲージ
		Texture::Draw2D(m_2p_gage_texture.c_str(), RIGHT_GAGE_POS_X, GagePosYCalc(m_p_player_manager->StaminaParcentageRelay(Player::STAR_2)));
	}

	// 左右ゲージ枠の岩
	Texture::Draw2D("Resource/Texture/UI/ui_left.png", 0.f, 0.f);
	Texture::Draw2D("Resource/Texture/UI/ui_right.png", RIGHT_ROCK_POS_X, 0.f);
}


void GameUI::GageColorChange() {
	// 自機1
	if (m_p_player_manager->StaminaParcentageRelay(Player::STAR_1) <= DANGER_LINE_PARCENTAGE) {
		m_1p_gage_texture = "Resource/Texture/UI/ui_red.png";
	}
	else {
		m_1p_gage_texture = "Resource/Texture/UI/ui_orange.png";
	}

	// 自機2
	if (m_p_player_manager->StaminaParcentageRelay(Player::STAR_2) <= DANGER_LINE_PARCENTAGE) {
		m_2p_gage_texture = "Resource/Texture/UI/ui_red.png";
	}
	else {
		m_2p_gage_texture = "Resource/Texture/UI/ui_violet.png";
	}
}


float GameUI::GagePosYCalc(float stamina_parcent) {
	return GAGE_UNDER_POS_Y - (ALL_GAGE * stamina_parcent);
}
