#include "GameUI.h"
#include "../Player/Player.h"
#include "../Lib/Sound/DirectSound.h"


GameUI::GameUI(Player* p_1, Player* p_2) {
	p1 = p_1;
	p2 = p_2;

	m_sort_object_type = SortObject::GAME_UI;
};


void GameUI::Update(){	
	// 片方死んだら片方も死ぬ
	if (p1->IsActive() == false|| p2->IsActive() == false) {
	    p1->EnableDead();
		p2->EnableDead();
	}
}


void GameUI::Draw() {

	// 黒バー
	// 右
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", 0.f, GAGE_MAX_POS);
	// 左
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", RIGHT_GAGE_POS, GAGE_MAX_POS);

	// HACK:Update内でやる
	if (p1->IsActive() == true&& p2->IsActive() == true) {

		static const float DANGER_LINE = 0.3f;
		// バーの色変更テストコード
		// オレンジバー
		if (StaminaParcentage(p1) <= DANGER_LINE) {
			Texture::Draw2D("Resource/Texture/UI/ui_red.png", 0.f, GagePosYCalc(StaminaParcentage(p1)));
		}
		else {
			Texture::Draw2D("Resource/Texture/UI/ui_ora.png", 0.f, GagePosYCalc(StaminaParcentage(p1)));
		}
		// ピンクバー
		if (StaminaParcentage(p2) <= DANGER_LINE) {
			Texture::Draw2D("Resource/Texture/UI/ui_red.png", RIGHT_GAGE_POS, GagePosYCalc(StaminaParcentage(p2)));
		}
		else {
			Texture::Draw2D("Resource/Texture/UI/ui_vio.png", RIGHT_GAGE_POS, GagePosYCalc(StaminaParcentage(p2)));
		}		
	}
	
	// 岩
	Texture::Draw2DUVShift("Resource/Texture/UI/ui_lef.png", 0.f, 0.f,0.f,0.f);
	Texture::Draw2D("Resource/Texture/UI/ui_rig.png", RIGHT_ROCK_POS, 0.f);
}


float GameUI::StaminaParcentage(Player* p) {
	float parcentage = (float)p->GetStamina() / (float)p->MAX_STAMINA;
	return parcentage;
}


float GameUI::GagePosYCalc(float stamina_parcent) {
	float gage_pos_y = GAGE_UNDER_POS - (ALL_GAGE * stamina_parcent);
	return gage_pos_y;
}
