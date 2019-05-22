#pragma once

#include"../SceneBase.h"


class Clear :public SceneBase {
public:
	~Clear() {}

	void Init()override;
	void Update()override;
	void Draw()override;
	SceneId End()override;
	SceneId Control()override;
};
