#include "GameUI.h"


GameUI::GameUI(Player* p_1, Player* p_2) {
	p1 = p_1;
	p2 = p_2;
	m_sort_object = SortObject::GAME_UI;
	count = 0;
};


void GameUI::Update(){
	p1_stamina_parcent = StaminaParcentage(p1);
	p2_stamina_parcent = StaminaParcentage(p2);
}


void GameUI::Draw() {

	// 黒バー
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", 0.f, GAGE_MAX_POS);
	// 黒バー
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", RIGHT_GAGE_POS, GAGE_MAX_POS);

	// オレンジバー
	Texture::Draw2D("Resource/Texture/UI/ui_ora.png", 0.f, GagePosYCalc(p1_stamina_parcent));
	
	// ピンクバー
	Texture::Draw2D("Resource/Texture/UI/ui_vio.png", RIGHT_GAGE_POS, GagePosYCalc(p2_stamina_parcent));
	
	// 岩
	Texture::Draw2DUVShift("Resource/Texture/UI/ui_lef.png", 0.f, 0.f,-0.01f,0.f);
	Texture::Draw2D("Resource/Texture/UI/ui_rig.png", RIGHT_ROCK_POS, 0.f);

	// しっぱいロゴ
	if (p1->GetIsAlive() == false || p2->GetIsAlive() == false) {
		Texture::Draw2D("Resource/Texture/UI/over_logo.png", 300, 0+ FailedCount());
	}
}


float GameUI::StaminaParcentage(Player* p) {
	float parcentage = (float)p->GetStamina() / (float)p->MAX_STAMINA;
	return parcentage;
}


float GameUI::GagePosYCalc(float stamina_parcent) {
	float gage_pos_y = GAGE_UNDER_POS - (ALL_GAGE * stamina_parcent);
	return gage_pos_y;
}


int GameUI::FailedCount() {
	if (count <= 100) {
		++count;
	}
	return count;
}
