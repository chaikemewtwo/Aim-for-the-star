#pragma once

#include<string>
#include"../GameInput/GameInput.h"
#include"../Lib/Sound/DirectSound.h"


// シーンID
enum SceneId {
	TITLE,
	GAME_MAIN,
	CLEAR,
	SCENE_QUIT
};


// シーンの基底クラス
class SceneBase {
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	SceneId End() {
	
		// ステップの初期化と次のシーンを返す
		m_scene_step = SceneStep::INIT;
		return m_new_scene_id;
	}

	SceneId Control() {

		switch (m_scene_step) {

		case SceneStep::INIT:
			Init();
			break;
		case SceneStep::UPDATE:
			Update();
			break;
		case SceneStep::END:
			return End();
		}

		// 各シーンのIDを返す
		return m_scene_id;
	}

protected:
	// シーン内処理のステップ
	enum SceneStep {
		INIT,
		UPDATE,
		END
	};


protected:
	SceneStep m_scene_step;		// シーン内のステップ
	SceneId m_scene_id;			// 各シーンのID
	SceneId m_new_scene_id;		// 次のシーンのID

	GameInput* m_p_game_input;	// 操作入力クラス
	Audio& m_audio = Audio::getInterface();
};
