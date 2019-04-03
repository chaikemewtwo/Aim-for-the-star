#pragma once
#include"../ObjectManager.h"


class GameScene {

public:

	GameScene() {}

	void Update() {
		m_object_manager.Update();
	}

	void Draw() {
		m_object_manager.Draw();
	}

private:
	ObjectManager m_object_manager;
};