#include"ClearScene.h"
#include"../../Lib/Texture/TextureBoad2D.h"


Clear::Clear() {
	m_scene_step = INIT;

	// プレイヤー1の画像登録
	m_player1_texture_list[FLIGHT_TEXTURE] = "Resource/Texture/Player/de_crear_01.png";
	m_player1_texture_list[CLEAR_POSE_TEXTURE] = "Resource/Texture/Player/de_crear_02.png";

	// プレイヤー2の画像登録
	m_player2_texture_list[FLIGHT_TEXTURE] = "Resource/Texture/Player/hi_crear_01.png";
	m_player2_texture_list[CLEAR_POSE_TEXTURE] = "Resource/Texture/Player/hi_crear_02.png";

	// 背景の画像登録
	m_background_texture_list[SEA_TEXTURE] = "Resource/Texture/Map/bg_clear_01.png";
	m_background_texture_list[SKY_TEXTURE] = "Resource/Texture/Map/bg_clear_02.png";
	m_background_texture_list[MOON_TEXTURE] = "Resource/Texture/Map/bg_clear_03.png";
}
//――――――――――――――――――――――――――――――――

void Clear::Init() {
	SceneBase::m_scene_id = CLEAR;
	m_scene_step = UPDATE;

	m_player1_texture = m_player1_texture_list[FLIGHT_TEXTURE];
	m_player2_texture = m_player2_texture_list[FLIGHT_TEXTURE];
	m_background_texture = m_background_texture_list[SEA_TEXTURE];
	
	m_p1_pos = D3DXVECTOR2(760, 1000);
	m_p2_pos = D3DXVECTOR2(1160, 1000);
}
//――――――――――――――――――――――――――――――――

void Clear::Update() {
	if (m_pkey_bord.press(VK_SPACE)) {
		m_scene_step = END;
		m_scene_id = TITLE;
	}
}
//――――――――――――――――――――――――――――――――

void Clear::Draw() {
	// 背景の描画
	Texture::Draw2D(
		m_background_texture.c_str(),
		0, 0
	);

	// プレイヤーの描画
	Texture::Draw2D(
		m_player1_texture.c_str(),
		m_p1_pos.x, m_p1_pos.y,
		0.5, 0.5, 0, 0.5, 0.5,
		true, 4, 4, 0
	);
	Texture::Draw2D(
		m_player2_texture.c_str(),
		m_p2_pos.x, m_p2_pos.y,
		0.5, 0.5, 0, 0.5, 0.5,
		true, 4, 4, 0
	);
}
//―――――――――――――――――――――――――――――――――
