#include"TitleScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"
//#include"../../Lib/Input/KeyBord.h"


void Title::Init() {
	//m_pkey_bord = Keybord::getInterface();
	m_scene_id = TITLE;
	m_scene_step = UPDATE;
}

void Title::Update() {
	if(m_pkey_bord.on(VK_SPACE)) {
		m_scene_step = END;
		m_scene_id = GAME_MAIN;
	}
}

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

