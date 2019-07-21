#pragma once

#include<unordered_map>
#include"SceneBase.h"


// シーン管理クラス
class SceneManager {
public:
	// シングルトン
	static SceneManager* GetInstance();

	~SceneManager();

	void Init();
	void Update();
	void Draw();

	// 現在のシーンと次のシーンを比較して遷移する
	/*
	第1：m_new_scene_idをいれること
	*/
	void ChangeScene(SceneId new_scene_id);

	// 終了フラグのゲッター
	bool IsQuit();

private:
	SceneManager() {}

private:
	bool m_is_quit;			// ゲーム終了フラグ
	SceneId m_scene_id;		// 現在のシーン
	SceneId m_new_scene_id; // 新しいシーン

	SceneBase* m_scene;		// シーン

	std::unordered_map<SceneId, SceneBase*> m_scene_list;	// シーンリスト
};
