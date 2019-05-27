#include "GameUI.h"
#include "../Player/Player.h"
#include "../Lib/Sound/DirectSound.h"


GameUI::GameUI(Player* p_1, Player* p_2) {
	p1 = p_1;
	p2 = p_2;
	m_sort_object = SortObject::GAME_UI;
	count = 0.f;
};


void GameUI::Update(){
	Audio& audio = Audio::getInterface();
	p1_alive = p1->GetIsAlive();
	p2_alive = p2->GetIsAlive();
	
	// 片方死んだら片方も死ぬ
	
	if (p1_alive == false|| p2_alive == false) {
	    p1->DisableIsAlive();
		p2->DisableIsAlive();
		
		if (p1_alive == false && p2_alive == false) {
			auto sound = audio.getBuffer("Resource/Sound/Player/ko1.wav");
			sound->Play(0, 0, 0);
		}
	}
	

	p1_stamina_parcent = StaminaParcentage(p1);
	p2_stamina_parcent = StaminaParcentage(p2);
}


void GameUI::Draw() {

	// 黒バー
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", 0.f, GAGE_MAX_POS);
	// 黒バー
	Texture::Draw2D("Resource/Texture/UI/ui_bla.png", RIGHT_GAGE_POS, GAGE_MAX_POS);


	if (p1_alive == true&& p2_alive == true) {
		// バーの色変更テストコード
		// オレンジバー
		if (p1_stamina_parcent <= 0.2f) {
			Texture::Draw2D("Resource/Texture/UI/ui_vio.png", 0.f, GagePosYCalc(p1_stamina_parcent));
		}
		else {
			Texture::Draw2D("Resource/Texture/UI/ui_ora.png", 0.f, GagePosYCalc(p1_stamina_parcent));
		}

		// ピンクバー
		Texture::Draw2D("Resource/Texture/UI/ui_vio.png", RIGHT_GAGE_POS, GagePosYCalc(p2_stamina_parcent));
	}
	
	
	// 岩
	Texture::Draw2DUVShift("Resource/Texture/UI/ui_lef.png", 0.f, 0.f,-0.01f,0.f);
	Texture::Draw2D("Resource/Texture/UI/ui_rig.png", RIGHT_ROCK_POS, 0.f);

	// しっぱいロゴ
	if (p1->GetIsAlive() == false || p2->GetIsAlive() == false) {
		Texture::Draw2D("Resource/Texture/UI/over_logo.png", 300.f, -450.f + FailedCount());
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


float GameUI::FailedCount() {
	if (count <= 550.f) {
		count += 3.f;
	}
	return count;
}
