#pragma once

#include"../SceneBase.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"


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
	IDirectSoundBuffer8* m_main_bgm;// = m_paudio.getBuffer("Resource/Sound/BGM/main_bgm.wav");
};
