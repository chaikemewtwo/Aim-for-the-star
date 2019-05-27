#pragma once

#include<string>
#include"../SceneBase.h"
#include"../../Lib/Window/Window.h"


class Title :public SceneBase {
public:
	Title();
	~Title() {}

private:
	enum ButtonTexture {
		DESCRIPTION_BUTTON,
		START_BUTTON,
		RETURN_BUTTON,
		TITLE_BUTTON_MAX
	};


	void Init()override;
	void Update()override;
	void Draw()override;

	void ButtonChange();

private:
	int m_button_check_num;
	std::string m_button_texture;
	std::string m_button_texture_list[TITLE_BUTTON_MAX];

	const float TITLE_LOGO_POS_X = WINDOW_W_F / 2;
	const float TITLE_LOGO_POS_Y = (WINDOW_H_F / 2) - 70;
	const float TITLE_BUTTON_POS_X = WINDOW_W_F / 2;
	const float TITLE_BUTTON_POS_Y = WINDOW_H_F-100;

	// ロゴと背景の画像を登録
	const std::string TITLE_TEXTURE = "Resource/Texture/Title/タイトル　背景.png";
	const std::string TITLE_LOGO = "Resource/Texture/Title/タイトル　ロゴ.png";
};
