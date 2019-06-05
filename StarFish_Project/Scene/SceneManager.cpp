#include"SceneManager.h"
#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"
#include"ClearScene/ClearScene.h"


SceneManager* SceneManager::GetInstance() {

	static SceneManager s_sm;
	return &s_sm;
}
//――――――――――――――――――――――――

SceneManager::~SceneManager() {

	for (auto i : m_scene_list) {

		if (&i != nullptr) {
			delete i.second;
		}
	}
}
//――――――――――――――――――――――――

void SceneManager::Init() {

	// シーンの登録
	m_scene_list.emplace(TITLE, new Title());
	m_scene_list.emplace(GAME_MAIN, new GameMain());
	m_scene_list.emplace(CLEAR, new Clear());

	// タイトルで初期化
	m_scene_id = SceneId::TITLE;
	m_scene = m_scene_list[m_scene_id];
}
//―――――――――――――――――――――――――

void SceneManager::Update() {

	ChangeScene(m_new_scene_id);
	m_new_scene_id = m_scene->Control();
}
//―――――――――――――――――――――――――

void SceneManager::Draw() {
	m_scene->Draw();
}
//―――――――――――――――――――――――――

void SceneManager::ChangeScene(SceneId new_scene_id) {

	if (new_scene_id == m_scene_id) {
		return;
	}
	else if (new_scene_id == SCENE_QUIT) {

		m_is_quit = true;
		return;
	}

	// 次のシーンを代入
	m_scene_id = new_scene_id;
	m_scene = m_scene_list.find(m_scene_id)->second;
}
//―――――――――――――――――――――――――

bool SceneManager::IsQuit() {

	if (m_is_quit == true) {
		return true;
	}
	
	return false;
}
//―――――――――――――――――――――――――
