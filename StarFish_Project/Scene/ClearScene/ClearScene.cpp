#include"ClearScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Window/Window.h"


Clear::Clear() {

	m_scene_step = INIT;

	// プレイヤー1の画像登録
	m_player1_texture_list[FLIGHT_TEXTURE] = "Resource/Texture/Player/hi_clear_01.png";
	m_player1_texture_list[CLEAR_POSE_TEXTURE] = "Resource/Texture/Player/hi_clear_02.png";

	// プレイヤー2の画像登録
	m_player2_texture_list[FLIGHT_TEXTURE] = "Resource/Texture/Player/de_clear_01.png";
	m_player2_texture_list[CLEAR_POSE_TEXTURE] = "Resource/Texture/Player/de_clear_02.png";

	// 背景の画像登録
	m_background_texture_list[SEA_TEXTURE] = "Resource/Texture/Map/bg_clear_01.png";
	m_background_texture_list[SKY_TEXTURE] = "Resource/Texture/Map/bg_clear_02.png";
	m_background_texture_list[MOON_TEXTURE] = "Resource/Texture/Map/bg_clear_03.png";
}
//――――――――――――――――――――――――――――――――

void Clear::Init() {

	SceneBase::m_scene_id = CLEAR;
	m_scene_step = UPDATE;

	// 画像の初期化
	m_player1_texture = m_player1_texture_list[FLIGHT_TEXTURE];
	m_player2_texture = m_player2_texture_list[FLIGHT_TEXTURE];

	m_background_texture1 = m_background_texture_list[SEA_TEXTURE];
	m_background_texture2 = m_background_texture_list[SKY_TEXTURE];
	
	// 座標の初期化
	m_player1_pos = D3DXVECTOR2((WINDOW_W_F/2)-256, 1000);
	m_player2_pos = D3DXVECTOR2((WINDOW_W_F/2)+256, 1000);

	m_background1_pos = D3DXVECTOR2(0, (WINDOW_H_F-BACKGROUND_TEXTURE_SIZE_Y));
	m_background2_pos = D3DXVECTOR2(0,m_background1_pos.y-BACKGROUND_TEXTURE_SIZE_Y);

	m_scene_change_time = 150;
	m_scene_change_count_timer = 0;
	m_clear_ui_size = 0;
	m_clear_ui_size_chnage_speed = 0.025f;
	m_is_clear_ui_size_max = false;

	// プレイヤーの変数初期化
	m_player_animation_finish = false;
	m_player_move_speed = 5;
	m_player_animation_max = 16;
	m_player_animation_num = 0;
	m_player_animation_change_time = 5;
	m_player_animation_timer = 0;

	// 背景の変数初期化
	m_is_background_move = false;
	m_background_move_speed = 15;

	// エフェクトの変数初期化
	m_effect_animation_num = 0;
	m_effect_animation_max = 13;
	m_effect_animation_timer = 0;
	m_effect_animation_change_time = 7;
	m_effect_lag_time = 40;
	m_effect_lag_count = 0;
}
//――――――――――――――――――――――――――――――――

void Clear::Update() {

	// プレイヤーの移動
	if (m_player1_pos.y >= 750 && m_player2_pos.y >= 750) {

		m_player1_pos.y -= m_player_move_speed;
		m_player2_pos.y -= m_player_move_speed;

		if (m_player1_pos.y <= 950 && m_player2_pos.y <= 950) {

			m_is_background_move = true;
			m_player_move_speed -= 0.01f;
		}
	}
	
	// 背景の移動
	if (m_is_background_move) {

		m_background1_pos.y += m_background_move_speed;
		m_background2_pos.y += m_background_move_speed;

		// 1枚目が描画し終わったら、3枚目の画像を入れる
		if (m_background1_pos.y >= BACKGROUND_TEXTURE_SIZE_Y) {

			m_background_texture1 = m_background_texture_list[MOON_TEXTURE];
			m_background1_pos.y = m_background2_pos.y-BACKGROUND_TEXTURE_SIZE_Y;
		}
		// 2枚目を描画し終わったら移動を止める
		else if (m_background2_pos.y >= BACKGROUND_TEXTURE_SIZE_Y) {
			m_is_background_move = false;
		}
	}

	// エフェクトの再生後、時間経過でタイトルに遷移
	//if (m_effect_animation_num >= m_effect_animation_max) {
	//	if (m_scene_change_time <= m_scene_change_count_timer) {
	//		m_scene_step = END;
	//		m_scene_id = TITLE;
	//	}
	//	else {
	//		m_scene_change_count_timer++;
	//	}
	//}

	// エフェクトのラグが終われば、UIを描画サイズまで徐々に大きくする 
	if (m_player_animation_finish == true && m_is_clear_ui_size_max == false && m_player_animation_num >= 6 && m_clear_ui_size <= 1) {
		m_clear_ui_size += m_clear_ui_size_chnage_speed;
		if (m_clear_ui_size >= 1) {
			m_is_clear_ui_size_max = true;
			m_clear_ui_size_chnage_speed = 0.001f;
		}
	}
	else if (m_is_clear_ui_size_max == true) {
		m_clear_ui_size -= m_clear_ui_size_chnage_speed;
		if (m_clear_ui_size <= 0.9) {
			m_is_clear_ui_size_max = false;
		}
	}


	// デバック用　クリア→タイトル
	if (m_pkey_bord.press(VK_SPACE)) {
		m_scene_step = END;
		m_scene_id = TITLE;
	}
}
//――――――――――――――――――――――――――――――――

void Clear::Draw() {

	// 背景の描画
	Texture::Draw2D(
		m_background_texture1.c_str(),
		m_background1_pos.x,m_background1_pos.y
	);
	Texture::Draw2D(
		m_background_texture2.c_str(),
		m_background2_pos.x, m_background2_pos.y
	);

	// エフェクトの描画
	if (m_player_animation_num >= 6 && m_player_animation_finish == true) {
		Texture::Draw2D(
			m_clear_effect.c_str(),
			m_player1_pos.x, m_player1_pos.y,
			0.25, 0.25, 0, 0.5, 0.5,
			true, EFFECT_TEXTURE_PARTITION_NUM, EFFECT_TEXTURE_PARTITION_NUM,
			m_effect_animation_num
		);
		Texture::Draw2D(
			m_clear_effect.c_str(),
			m_player2_pos.x, m_player2_pos.y,
			0.25, 0.25, 0, 0.5, 0.5,
			true, EFFECT_TEXTURE_PARTITION_NUM, EFFECT_TEXTURE_PARTITION_NUM,
			m_effect_animation_num
		);
		EffectAnimation();

		Texture::Draw2D(
			m_clear_ui_texture.c_str(),
			WINDOW_W_F / 2, m_player1_pos.y - 500,
			m_clear_ui_size, m_clear_ui_size, 0, 0.5, 0.5
		);
	}

	// プレイヤーの描画
	Texture::Draw2D(
		m_player1_texture.c_str(),
		m_player1_pos.x, m_player1_pos.y,
		0.25, 0.25, 0, 0.5, 0.5,
		true, PLAYER_TEXTURE_PARTITION_NUM, PLAYER_TEXTURE_PARTITION_NUM, 
		m_player_animation_num
	);
	Texture::Draw2D(
		m_player2_texture.c_str(),
		m_player2_pos.x, m_player2_pos.y,
		0.25, 0.25, 0, 0.5, 0.5,
		true, PLAYER_TEXTURE_PARTITION_NUM, PLAYER_TEXTURE_PARTITION_NUM, 
		m_player_animation_num
	);
	PlayerAnimation();
}
//―――――――――――――――――――――――――――――――――

void Clear::PlayerAnimation() {

	// アニメーションが回り切っていたら
	if (m_player_animation_finish == true && m_player_animation_num == 15) {
		m_player_animation_num = 15;
	}
	// 回り切っていなければアニメーションする
	else{
		if (m_player_animation_timer >= m_player_animation_change_time) {

			m_player_animation_timer = 0;
			m_player_animation_num++;

			// 背景が途中の場合、アニメーションをループさせる
			if (m_background2_pos.y <= WINDOW_H_F && m_player_animation_num == 13) {
				m_player_animation_num = 5;
			}
			// 背景スクロール後、アニメーションを次に遷移させる
			else if (m_player_animation_num >= m_player_animation_max && m_player_animation_finish == false) {

				m_player1_texture = m_player1_texture_list[CLEAR_POSE_TEXTURE];
				m_player2_texture = m_player2_texture_list[CLEAR_POSE_TEXTURE];
				m_player_animation_num = 0;
				m_player_animation_finish = true;
			}
		}
		else {
			m_player_animation_timer++;
		}
	}
}
//―――――――――――――――――――――――――――――――――

void Clear::EffectAnimation() {

	if (m_effect_animation_timer >= m_effect_animation_change_time) {
		m_effect_animation_timer = 0;
		m_effect_animation_num++;
		if (m_effect_animation_num >= m_effect_animation_max) {
			m_effect_animation_num = 0;
		}
	}
	else {
		m_effect_animation_timer++;
	}
}
//―――――――――――――――――――――――――――――――――
