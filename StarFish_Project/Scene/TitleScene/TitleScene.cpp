#include"TitleScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"


Title::Title() {

	m_scene_step = SceneStep::INIT;
	m_p_game_input = new GameInput;
	// 画像の登録
	m_button_texture_list[DESCRIPTION_BUTTON] = "Resource/Texture/UI/title_button03.png";
	m_button_texture_list[START_BUTTON] = "Resource/Texture/UI/title_button01.png";
	m_button_texture_list[RETURN_BUTTON] = "Resource/Texture/UI/title_button02.png";

	// サウンドの登録
	m_p_title_bgm = m_audio.getBuffer("Resource/Sound/BGM/title_bgm.wav");
}
//―――――――――――――――――――

void Title::Init() {

	m_scene_id = SceneId::TITLE;
	m_scene_step = SceneStep::UPDATE;

	// ボタンの設定の初期化
	m_button_texture = m_button_texture_list[START_BUTTON];
	m_button_check_num = 1;

	// サウンドの初期化
	m_p_title_bgm->SetCurrentPosition(0);

	// BGMの再生
	if (m_p_title_bgm != nullptr) {
		m_p_title_bgm->Play(0, 0, DSBPLAY_LOOPING);
	}
}
//―――――――――――――――――――

void Title::Update() {
	
	//m_p_game_input->Update();
	CheckChangeButton();

	if (m_p_game_input->InputCommand(m_p_game_input->P1_DECIDE_BUTTON) ||
		m_p_game_input->InputCommand(m_p_game_input->P2_DECIDE_BUTTON) || m_p_game_input->InputCommand(m_p_game_input->START_BUTTON)){

		if (m_button_check_num == START_BUTTON) {
			
			m_p_title_bgm->Stop();
			m_scene_step = SceneStep::END;
			m_new_scene_id = SceneId::GAME_MAIN;
		}
		else if (m_button_check_num == RETURN_BUTTON) {

			m_p_title_bgm->Stop();
			m_scene_step = SceneStep::END;
			m_new_scene_id = SceneId::SCENE_QUIT;
		}
	}
	
	// デバック用　タイトル→ゲームメイン
	//if(m_pkey_bord.press(VK_F1)) {

	//	m_p_title_bgm->Stop();
	//	m_scene_step = SceneStep::END;
	//	m_new_scene_id = SceneId:: GAME_MAIN;
	//}
}
//―――――――――――――――――――

void Title::Draw() {

	// 背景の描画
	Texture::Draw2D(
		TITLE_TEXTURE.c_str(),0,0
	);

	// タイトルロゴの描画
	Texture::Draw2D(
		TITLE_LOGO.c_str(),
		TITLE_LOGO_POS.x, TITLE_LOGO_POS.y,
		1, 1, 0, 0.5, 0.5
	);

	// UIのボタン描画
	Texture::Draw2D(
		m_button_texture.c_str(),
		TITLE_BUTTON_POS.x, TITLE_BUTTON_POS.y,
		1, 1, 0, 0.5, 0.5
	);
}
//―――――――――――――――――――

// 説明、スタート、終わるのボタン選択処理
void Title::CheckChangeButton() {
	static int count = 10;
	++count;
	if (count >= 10) {
		if (m_p_game_input->InputCommand(m_p_game_input->TITLE_LEFT_BUTTON) == true &&
			m_button_check_num > DESCRIPTION_BUTTON) {

			m_button_check_num--;
			if (m_button_check_num == DESCRIPTION_BUTTON) {
				m_button_texture = m_button_texture_list[DESCRIPTION_BUTTON];
			}
			else if (m_button_check_num == START_BUTTON) {
				m_button_texture = m_button_texture_list[START_BUTTON];
			}
			count = 0;
		}

		else if (m_p_game_input->InputCommand(m_p_game_input->TITLE_RIGHT_BUTTON) == true &&
			m_button_check_num < RETURN_BUTTON) {

			m_button_check_num++;
			if (m_button_check_num == START_BUTTON) {
				m_button_texture = m_button_texture_list[START_BUTTON];
			}
			else if (m_button_check_num == RETURN_BUTTON) {
				m_button_texture = m_button_texture_list[RETURN_BUTTON];
			}
			count = 0;
		}
	}
}
//―――――――――――――――――――
