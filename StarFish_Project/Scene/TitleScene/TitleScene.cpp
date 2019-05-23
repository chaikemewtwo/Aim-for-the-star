#include"TitleScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"


Title::Title() {
	m_scene_step = INIT;
}
//―――――――――――――――――――

void Title::Init() {
	m_scene_id = TITLE;
	m_scene_step = UPDATE;
}
//―――――――――――――――――――

void Title::Update() {

	// デバック用　タイトル→ゲームメイン
	if(m_pkey_bord.press(VK_SPACE)) {
		m_scene_step = END;
		m_scene_id = GAME_MAIN;
	}
}
//―――――――――――――――――――

void Title::Draw() {
	Texture::Draw2D(
		TITLE_TEXTURE.c_str(),0,0
	);

	Texture::Draw2D(
		TITLE_LOGO.c_str(),
		TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y,
		1, 1, 0, 0.5, 0.5
	);
}
//―――――――――――――――――――
