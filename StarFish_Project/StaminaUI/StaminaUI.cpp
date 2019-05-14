#include "StaminaUI.h"


StaminaUI::StaminaUI(Player* p_1, Player* p_2) {
	p1 = p_1;
	p2 = p_2;
};


void StaminaUI::Update(){
	p1_stamina_parcent = StaminaParcentage(p1);
	p2_stamina_parcent = StaminaParcentage(p2);
}


void StaminaUI::Draw() {
	// 黒バー
	Texture::Draw2D("Resource/Texture/UI/UI　黒.png", 0.f, 0.f);

	// オレンジバー
	Texture::Draw2D("Resource/Texture/UI/UI　橙バー.png", 0.f, GagePosYCalc(p1_stamina_parcent));
	
	// ピンクバー
	Texture::Draw2D("Resource/Texture/UI/UI　紫バー.png", 0.f, GagePosYCalc(p2_stamina_parcent));
	
	// 岩
	Texture::Draw2D("Resource/Texture/UI/UI 岩.png", 0.f, 0.f);
}


float StaminaUI::StaminaParcentage(Player* p) {
	float parcentage = (float)p->GetStamina() / (float)p->MAX_STAMINA;
	return parcentage;
}


float StaminaUI::GagePosYCalc(float stamina_parcent) {
	float gage_pos_y = GAGE_UNDER_POS - (ALL_GAGE * stamina_parcent);
	return gage_pos_y;
}
