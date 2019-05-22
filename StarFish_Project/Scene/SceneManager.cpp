#include"SceneManager.h"
#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"
#include"ClearScene/ClearScene.h"


SceneManager* SceneManager::GetInstance() {
	static SceneManager s_sm;
	return &s_sm;
}


SceneManager::~SceneManager() {
	for (auto i : m_scene_list) {
		if (&i != nullptr) {
			delete i.second;
		}
	}
}


void SceneManager::Init() {
	// シーンの登録
	m_scene_list.emplace(TITLE, new Title());
	m_scene_list.emplace(GAME_MAIN, new GameMain());
	m_scene_list.emplace(CLEAR, new Clear());

	// タイトルで初期化
	m_scene_id = TITLE;
	m_scene = m_scene_list[m_scene_id];
}


void SceneManager::Update() {
	SceneId scene_id;
	scene_id = m_scene->Control();
	ChangeScene(scene_id);
}


void SceneManager::ChangeScene(SceneId scene_id) {
	if (scene_id == m_scene_id) {
		return;
	}

	// 次のシーンを代入
	m_scene_id = scene_id;
	m_scene = m_scene_list.find(m_scene_id)->second;
}
