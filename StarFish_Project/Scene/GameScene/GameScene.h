#pragma once

#include"../SceneBase.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../../Player/Player.h"


class GameMain :public SceneBase {
public:
	GameMain();
	~GameMain() {}

private:
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	ObjectManager * m_pobj_mng;
};
