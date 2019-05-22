#pragma once


enum SceneId {
	TITLE,
	GAME_MAIN,
	CLEAR
};

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
	virtual SceneId End() = 0;
	virtual SceneId Control() = 0;

protected:
	SceneStep m_scene_step;
};
