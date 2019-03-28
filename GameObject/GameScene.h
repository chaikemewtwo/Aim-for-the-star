#pragma once
#include"../GameObject/Manager/TaskManager.h"
#include"../Object/GameObject/ObjectManager.h"

class GameScene {

public:

	GameScene() {
		obj_mng = new ObjectManager;
		tm = new TaskManager(obj_mng->GetObjectData());
	}

	void Update() {
		obj_mng->Update();
		tm->Update();
	}

private:
	ObjectManager *obj_mng;
	TaskManager *tm;
};