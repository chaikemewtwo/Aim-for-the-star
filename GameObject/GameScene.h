#pragma once
#include"../GameObject/ObjectManagerToDoRegistr.h"


/* ゲームシーンクラスの例です */

class GameScene {

public:

	GameScene() {}

	void Update() {
		// 更新
		m_object_manager.Update();
	}

	void Draw() {
		// 描画
		m_object_manager.Draw();
	}

private:

	// オブジェクトの生成管理者をここで定義
	ObjectManagerToDoRegistr m_object_manager;
};