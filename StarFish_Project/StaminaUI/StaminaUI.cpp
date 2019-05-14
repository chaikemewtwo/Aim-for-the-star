#include "StaminaUI.h"


StaminaUI::StaminaUI(Player* p_1, Player* p_2) {
	// テスト用
	y = ALL_GAGE;
	p1 = p_1;
	p2 = p_2;
};


void StaminaUI::Update(){
	Keybord& kb = Keybord::getInterface();
	//float stamina_parcentage(p1)

	// テスト用
	++y;
	if (kb.press(VK_SPACE)) {
		y -= 100.f;
	}
}

void StaminaUI::Draw() {
	// 黒バー
	Texture::Draw2D("Resource/Texture/UI/UI　黒.png", 0, 0);

	// オレンジバー
	//Texture::Draw2D("Resource/Texture/UI/UI　橙バー.png", 0, stamina_parcentage(p1), 1.f, 1.f);
	// テスト用
	Texture::Draw2D("Resource/Texture/UI/UI　橙バー.png", 0, GAGE_UNDER_POS - y, 1.f, 1.f);
	
	// ピンクバー
	Texture::Draw2D("Resource/Texture/UI/UI　紫バー.png", 0, 0, 1.f, 1.f);
	// テスト用
	//Texture::Draw2D("Resource/Texture/UI/UI　紫バー.png", 0, 1000 , 1.f, 1.f);
	
	// 岩
	Texture::Draw2DGraph("Resource/Texture/UI/UI 岩.png", 0, 0);
}

float StaminaUI::stamina_parcentage(Player* p) {
	float parcentage = p->GetStamina() / p->MAX_STAMINA;
	return parcentage;
}
