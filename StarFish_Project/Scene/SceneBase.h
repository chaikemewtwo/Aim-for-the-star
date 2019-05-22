#pragma once

#include"../Lib/Input/KeyBord.h"


// シーンID
enum SceneId {
	TITLE,
	GAME_MAIN,
	CLEAR
};

// シーン内処理のステップ
enum SceneStep {
	INIT,
	UPDATE,
	END
};

class SceneBase {
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual SceneId End() {
		// ステップの初期化と次のシーンを返す
		m_scene_step = INIT;
		return m_scene_id;
	}

	virtual SceneId Control() {
		switch (m_scene_step) {
		case INIT:
			Init();
			return m_scene_id;
		case UPDATE:
			Update();
			Draw();
			return m_scene_id;
		case END:
			return End();
		}

		return m_scene_id;
	}

protected:
	SceneStep m_scene_step;
	SceneId m_scene_id;

	Keybord& m_pkey_bord = Keybord::getInterface();
};
