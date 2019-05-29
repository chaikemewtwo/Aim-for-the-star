#include"GameScene.h"


GameMain::GameMain() {
	m_scene_step = INIT;
}
//―――――――――――――――――――

void GameMain::Init() {
	m_scene_id = GAME_MAIN;
	m_scene_step = UPDATE;

	m_pobj_mng = new ObjectManager;
}
//―――――――――――――――――――

void GameMain::Update() {

	m_pobj_mng->Update();	

	// デバック用のクリア・ゲームオーバー確認コマンド
	if (m_pkey_bord.press(VK_F1)) {
		m_pobj_mng->IsGameover(true);
	}
	else if (m_pkey_bord.press(VK_F2)) {
		m_pobj_mng->IsClear(true);
	}
	
	if (m_pobj_mng->ClearEnable() == true) {
		m_scene_step = END;
		m_scene_id = CLEAR;
	}
	else if (m_pobj_mng->GameOverEnable() == true) {
		m_scene_step = END;
		m_scene_id = TITLE;
	}

	// デバック用　ゲームシーン→クリア
	if (m_pkey_bord.press(VK_SPACE)) {
		m_scene_step = END;
		m_scene_id = CLEAR;
	}
}
//―――――――――――――――――――

void GameMain::Draw() {
	m_pobj_mng->Draw();
}
//―――――――――――――――――――
