#pragma once

#include"../SceneBase.h"


class GameMain :public SceneBase {
public:
	~GameMain() {}

	void Init()override;
	void Update()override;
	void Draw()override;
	SceneId End()override;
	SceneId Control()override;
};
