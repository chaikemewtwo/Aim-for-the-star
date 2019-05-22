#pragma once

#include"../SceneBase.h"


class Title :public SceneBase {
public:
	~Title() {}

	void Init()override;
	void Update()override;
	void Draw()override;
	SceneId End()override;
	SceneId Control()override;
private:

};
