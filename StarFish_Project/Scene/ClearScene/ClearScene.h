#pragma once

#include<string>
#include<d3dx9.h>
#include"../SceneBase.h"


class Clear :public SceneBase {
public:
	Clear();
	~Clear() {}

private:
	enum BackGroundTex {
		SEA_TEXTURE,
		SKY_TEXTURE,
		MOON_TEXTURE,
		BG_TEX_MAX
	};

	enum PlayerClearTex {
		SWIM_TEXTURE,
		FLIGHT_TEXTURE,
		CLEAR_POSE_TEXTURE,
		CLEAR_TEXTURE_MAX
	};


	void Init()override;
	void Update()override;
	void Draw()override;

private:
	D3DXVECTOR2 m_p1_pos;
	D3DXVECTOR2 m_p2_pos;

	std::string m_player1_texture;
	std::string m_player2_texture;
	std::string m_background_texture;

	std::string m_player1_texture_list[CLEAR_TEXTURE_MAX];
	std::string m_player2_texture_list[CLEAR_TEXTURE_MAX];
	std::string m_background_texture_list[BG_TEX_MAX];

	const std::string m_clear_effect = "Resource/Texture/Effect/crear_eff.png";
};
