#include"GameScene.h"


GameMain::GameMain() {

	m_scene_step = INIT;	
	
	m_main_bgm = m_paudio.getBuffer("Resource/Sound/BGM/main_bgm.wav");

	m_gameover_jingle = m_paudio.getBuffer("Resource/Sound/Failed/game_over.wav");
}
//―――――――――――――――――――

void GameMain::Init() {

	m_scene_id = GAME_MAIN;
	m_scene_step = UPDATE;

	m_pobj_mng = new ObjectManager;

	m_gameover_ui_pos = D3DXVECTOR2((Window::WIDTH / 2), 0);
	m_gameover_ui_posy_max = 300;
	m_scene_change_count_timer = 0;
	m_gameover_scene_change_time = 360;

	m_main_bgm->SetCurrentPosition(0);
	m_gameover_jingle->SetCurrentPosition(0);
	if (m_main_bgm != nullptr) {
		m_main_bgm->Play(0, 0, DSBPLAY_LOOPING);
	}
}
//―――――――――――――――――――

void GameMain::Update() {

	m_pobj_mng->Update();	

	if (m_pobj_mng->IsGameOver() == true) {

		m_main_bgm->Stop();
		if (m_gameover_jingle != nullptr) {
			m_gameover_jingle->Play(0, 0, 0);
		}
	}

	if (m_pobj_mng->IsClear() == true) {
	
		m_main_bgm->Stop();
		m_scene_step = END;
		m_scene_id = CLEAR;
	}
	else if (m_pobj_mng->IsGameOver() == true && SceneChangeCheck() == true) {

		m_gameover_jingle->Stop();
		m_scene_step = END;
		m_scene_id = TITLE;
	}
}
//―――――――――――――――――――

void GameMain::Draw() {

	m_pobj_mng->Draw();

	if (m_pobj_mng->IsGameOver() == true) {
		Texture::Draw2D(
			m_gameover_ui.c_str(),
			m_gameover_ui_pos.x, m_gameover_ui_pos.y,
			1, 1, 0, 0.5, 0.5
		);
	}
}
//―――――――――――――――――――

bool GameMain::SceneChangeCheck() {

	if (m_gameover_ui_pos.y <= m_gameover_ui_posy_max) {
		m_gameover_ui_pos.y += 3.f;
	}
	else if (m_gameover_ui_pos.y >= m_gameover_ui_posy_max) {

		m_scene_change_count_timer++;
		if (m_gameover_scene_change_time <= m_scene_change_count_timer) {
			return true;
		}
	}
	return false;
}
//―――――――――――――――――――
