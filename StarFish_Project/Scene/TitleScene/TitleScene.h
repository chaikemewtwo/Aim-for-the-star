#pragma once

#include<string>
#include"../SceneBase.h"
#include"../../Lib/Window/Window.h"


class Title :public SceneBase {
public:

private:
	~Title() {}

	void Init()override;
	void Update()override;
	void Draw()override;

	//const float TEX_POS_X = WINDOW_W_F / 2;
	//const float TEX_POS_Y = WINDOW_H_F / 2;
	const float TITLE_LOGO_POS_X = WINDOW_W / 2;
	const float TITLE_LOGO_POS_Y = WINDOW_H / 2;

	const std::string TITLE_TEXTURE = "Resource/Texture/Title/タイトル　背景.png";
	const std::string TITLE_LOGO = "Resource/Texture/Title/タイトル　ロゴ.png";
};
