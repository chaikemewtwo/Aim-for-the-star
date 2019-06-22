#pragma once

#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"Player.h"


class PlayerManager {
public:
	PlayerManager(ObjectManager* obj_mng);

	void Update();
	void Draw();

private:
	ObjectManager * m_p_obj_mng;
};
