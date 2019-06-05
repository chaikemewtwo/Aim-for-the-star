#pragma once

#include<unordered_map>
#include"SceneBase.h"


class SceneManager {
public:
	static SceneManager* GetInstance();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void ChangeScene(SceneId scene_id);
	bool IsQuit();

private:
	SceneManager() {}

private:
	bool m_is_quit;			// ゲーム終了フラグ
	SceneId m_scene_id;		// 現在のシーン
	SceneId m_new_scene_id; // 新しいシーン

	SceneBase* m_scene;		// シーン

	std::unordered_map<SceneId, SceneBase*> m_scene_list;
};
