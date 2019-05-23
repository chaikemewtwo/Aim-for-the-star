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
