#pragma once
#include"../ObjectAndManagerUser.h"


class GameScene {

public:

	GameScene() {
	
	}

	void Update() {
		top_obj_mng.Update();
	}

	void Draw() {
		top_obj_mng.Draw();
	}

private:
	ObjectAndManagerUser top_obj_mng;
};