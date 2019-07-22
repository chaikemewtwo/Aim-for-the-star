#pragma once

#include<string>
#include"../../Lib/Window/Window.h"
#include"../SceneBase.h"


// タイトルシーンクラス
class Title :public SceneBase {
public:
	Title();
	~Title() {}

private:
	enum ButtonType {
		DESCRIPTION_BUTTON,
		START_BUTTON,
		RETURN_BUTTON,
		TITLE_BUTTON_MAX
	};


	void Init()override;
	void Update()override;
	void Draw()override;

	// どのボタンが選択されているかの確認
	void CheckChangeButton();

private:
	int m_button_check_num;			// 選択ボタンの判定数値

	std::string m_button_texture;	// 選択ボタン画像
	std::string m_button_texture_list[TITLE_BUTTON_MAX];	// 選択ボタン画像リスト

	// タイトルロゴの位置
	const D3DXVECTOR2 TITLE_LOGO_POS = { (Window::WIDTH / 2),(Window::HEIGHT / 2) - 70 };   
	// 選択ボタンの位置
	const D3DXVECTOR2 TITLE_BUTTON_POS = { (Window::WIDTH / 2),(Window::HEIGHT - 100) };	

	// ロゴと背景の画像を登録
	const std::string TITLE_TEXTURE = "Resource/Texture/Title/タイトル　背景.png";
	const std::string TITLE_LOGO = "Resource/Texture/Title/タイトル　ロゴ.png";

	IDirectSoundBuffer8* m_p_title_bgm;	// タイトルBGM
};
