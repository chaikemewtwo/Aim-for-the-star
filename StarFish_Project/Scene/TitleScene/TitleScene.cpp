#include"TitleScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"


Title::Title() {

	m_scene_step = SceneStep::INIT;
	m_p_game_input = new GameInput;
	// 画像の登録
	m_button_texture_list[MANUAL_BUTTON] = "Resource/Texture/UI/title_button03.png";
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
	m_button_texture = m_button_texture_list[ButtonType::START_BUTTON];
	m_button_check_num = ButtonType::START_BUTTON;

	m_is_manual = false;

	// サウンドの初期化
	m_p_title_bgm->SetCurrentPosition(0);

	// BGMの再生
	if (m_p_title_bgm != nullptr) {
		m_p_title_bgm->Play(0, 0, DSBPLAY_LOOPING);
	}
}
//―――――――――――――――――――

void Title::Update() {

	// ボタン選択のチェック
	CheckChangeButton();

	if (m_p_game_input->InputCommand(m_p_game_input->P1_DECIDE_BUTTON) ||
		m_p_game_input->InputCommand(m_p_game_input->P2_DECIDE_BUTTON) || 
		m_p_game_input->InputCommand(m_p_game_input->START_BUTTON)) {

		// 選択しているボタンに合わせて遷移
		// ゲーム開始
		if (m_button_check_num == ButtonType::START_BUTTON && m_is_manual == false) {

			m_p_title_bgm->Stop();
			m_scene_step = SceneStep::END;
			m_new_scene_id = SceneId::GAME_MAIN;
		}
		// 説明画面
		else if (m_button_check_num == ButtonType::MANUAL_BUTTON && m_is_manual == false) {

			m_is_manual = true;
		}
		// ゲーム終了
		else if (m_button_check_num == ButtonType::RETURN_BUTTON && m_is_manual == false) {

			m_p_title_bgm->Stop();
			m_scene_step = SceneStep::END;
			m_new_scene_id = SceneId::SCENE_QUIT;
		}
		else if (m_button_check_num == ButtonType::BACK_BUTTON && m_is_manual == true) {

			m_button_check_num = ButtonType::MANUAL_BUTTON;
			m_is_manual = false;
		}
	}
}
//―――――――――――――――――――

void Title::Draw() {

	
		// 背景の描画
		Texture::Draw2D(
			TITLE_TEXTURE.c_str(), 0, 0
		);
		
		if (m_is_manual == false) {
			// タイトルロゴの描画
			Texture::Draw2D(
				TITLE_LOGO.c_str(),
				TITLE_LOGO_POS.x, TITLE_LOGO_POS.y,
				1, 1, 0, 0.5f, 0.5f
			);

			// UIのボタン描画
			Texture::Draw2D(
				m_button_texture.c_str(),
				TITLE_BUTTON_POS.x, TITLE_BUTTON_POS.y,
				1, 1, 0, 0.5f, 0.5f
			);
		}
		else if (m_is_manual == true) {

			Texture::Draw2D(
				MANUAL_TEXTURE.c_str(),
				MANUAL_POS.x, MANUAL_POS.y,
				0.45f, 0.45f, 0, 0.5f, 0.5f);
		}
}
//―――――――――――――――――――

// 説明、スタート、終わるのボタン選択処理
void Title::CheckChangeButton() {

	static int count = 10;
	++count;

	if (count >= 10 && m_is_manual == false) {

		if (m_p_game_input->InputCommand(m_p_game_input->TITLE_LEFT_BUTTON) == true &&
			m_button_check_num > ButtonType::MANUAL_BUTTON) {

			m_button_check_num--;

			if (m_button_check_num == ButtonType::MANUAL_BUTTON) {
				m_button_texture = m_button_texture_list[ButtonType::MANUAL_BUTTON];
			}
			else if (m_button_check_num == START_BUTTON) {
				m_button_texture = m_button_texture_list[ButtonType::START_BUTTON];
			}

			count = 0;
		}
		else if (m_p_game_input->InputCommand(m_p_game_input->TITLE_RIGHT_BUTTON) == true &&
			m_button_check_num < ButtonType::RETURN_BUTTON) {

			m_button_check_num++;

			if (m_button_check_num == ButtonType::START_BUTTON) {
				m_button_texture = m_button_texture_list[ButtonType::START_BUTTON];
			}
			else if (m_button_check_num == ButtonType::RETURN_BUTTON) {
				m_button_texture = m_button_texture_list[ButtonType::RETURN_BUTTON];
			}

			count = 0;
		}
	}
	else if (m_is_manual == true) {
		m_button_check_num = ButtonType::BACK_BUTTON;
	}
}
//―――――――――――――――――――
