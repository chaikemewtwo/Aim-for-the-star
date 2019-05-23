#pragma once

#include<unordered_map>
#include"SceneBase.h"


class SceneManager {
public:
	static SceneManager* GetInstance();
	~SceneManager();

	void Init();
	void Update();
	void ChangeScene(SceneId scene_id);

private:
	SceneManager() {}

	std::unordered_map<SceneId, SceneBase*> m_scene_list;
	SceneBase* m_scene;		// シーン
	SceneId m_scene_id;		// シーン指定用の定数
};
