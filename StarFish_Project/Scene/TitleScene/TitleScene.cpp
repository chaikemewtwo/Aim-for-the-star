#include"TitleScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"


void Title::Init() {
	m_scene_step = UPDATE;
}

void Title::Update() {
	m_scene_step = END;
}

void Title::Draw() {
	
}

SceneId Title::End() {
	m_scene_step = INIT;
	return GAME_MAIN;
}

SceneId Title::Control() {
	switch (m_scene_step) {
	case INIT:
		Init();
		return TITLE;
	case UPDATE:
		Update();
		Draw();
		return TITLE;
	case END:
		return End();
	}

	return TITLE;
}
