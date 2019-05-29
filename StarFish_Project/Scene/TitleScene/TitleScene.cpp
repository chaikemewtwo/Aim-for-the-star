#include"TitleScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"


Title::Title() {

	m_scene_step = INIT;

	m_button_texture_list[DESCRIPTION_BUTTON] = "Resource/Texture/UI/title_button03.png";
	m_button_texture_list[START_BUTTON] = "Resource/Texture/UI/title_button01.png";
	m_button_texture_list[RETURN_BUTTON] = "Resource/Texture/UI/title_button02.png";

	m_title_bgm = m_paudio.getBuffer("Resource/Sound/BGM/title_bgm.wav");
}
//―――――――――――――――――――

void Title::Init() {

	m_scene_id = TITLE;
	m_scene_step = UPDATE;


	// ボタンの初期化
	m_button_texture = m_button_texture_list[START_BUTTON];
	m_button_check_num = 1;
	m_title_bgm->SetCurrentPosition(0);
}
//―――――――――――――――――――

void Title::Update() {
	if (m_title_bgm != nullptr) {
		m_title_bgm->Play(0, 0, DSBPLAY_LOOPING);
	}

	ButtonChange();

	if (m_pkey_bord.press(VK_RETURN)) {

		if (m_button_check_num == START_BUTTON) {
			
			m_title_bgm->Stop();
			m_scene_step = END;
			m_scene_id = GAME_MAIN;
		}
		else if (m_button_check_num == RETURN_BUTTON) {

			m_title_bgm->Stop();
			m_scene_step = END;
			m_scene_id = SCENE_QUIT;
		}
	}
	
	// デバック用　タイトル→ゲームメイン
	if(m_pkey_bord.press(VK_SPACE)) {

		m_title_bgm->Stop();
		m_scene_step = END;
		m_scene_id = GAME_MAIN;
	}
}
//―――――――――――――――――――

void Title::Draw() {

	// 背景の描画
	Texture::Draw2D(
		TITLE_TEXTURE.c_str(),0,0
	);

	// タイトルロゴの描画
	Texture::Draw2D(
		TITLE_LOGO.c_str(),
		TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y,
		1, 1, 0, 0.5, 0.5
	);

	// UIのボタン描画
	Texture::Draw2D(
		m_button_texture.c_str(),
		TITLE_BUTTON_POS_X, TITLE_BUTTON_POS_Y,
		1, 1, 0, 0.5, 0.5
	);
}
//―――――――――――――――――――

void Title::ButtonChange() {
	
	if (m_pkey_bord.press(VK_LEFT) && m_button_check_num > DESCRIPTION_BUTTON) {

		m_button_check_num--;
		if (m_button_check_num == DESCRIPTION_BUTTON) {
			m_button_texture = m_button_texture_list[DESCRIPTION_BUTTON];
		}
		else if (m_button_check_num == START_BUTTON) {
			m_button_texture = m_button_texture_list[START_BUTTON];
		}
	}
	if (m_pkey_bord.press(VK_RIGHT) && m_button_check_num < RETURN_BUTTON) {

		m_button_check_num++;
		if (m_button_check_num == START_BUTTON) {
			m_button_texture = m_button_texture_list[START_BUTTON];
		}
		else if (m_button_check_num == RETURN_BUTTON) {
			m_button_texture = m_button_texture_list[RETURN_BUTTON];
		}
	}
}
//―――――――――――――――――――
