#pragma once
#include"../WrapperObject.h"


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
	WrapperObject top_obj_mng;
};