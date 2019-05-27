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
		BG_TEXTURE_MAX
	};

	enum PlayerClearTex {
		FLIGHT_TEXTURE,
		CLEAR_POSE_TEXTURE,
		CLEAR_TEXTURE_MAX
	};

	void Init()override;
	void Update()override;
	void Draw()override;
	//void AnimationDraw(std::string animation_textur, int max_animation, int change_time, int new_texture);
	void PlayerAnimation();

private:
	int m_player_animation_timer;				// プレイヤーのカウント用
	int m_player_animation_change_time;			// アニメーションの遷移時間
	int m_player_animation_num;					// プレイヤーのアニメーション番号
	int m_player_animation_max;					// プレイヤーのアニメーション数
	float m_player_move_speed;					// プレイヤーの移動速度
	float m_background_move_speed;				// 背景の移動速度
	bool m_is_background_move;					// 背景を動かすフラグ
	bool m_player_animation_finish;

	D3DXVECTOR2 m_background1_pos;				// 背景の位置１
	D3DXVECTOR2 m_background2_pos;				// 背景の位置２
	D3DXVECTOR2 m_player1_pos;					// プレイヤーの位置１
	D3DXVECTOR2 m_player2_pos;					// プレイヤーの位置2

	// 各画像用の変数
	std::string m_player1_texture;
	std::string m_player2_texture;
	std::string m_background_texture1;
	std::string m_background_texture2;

	// 各画像のリスト
	std::string m_player1_texture_list[CLEAR_TEXTURE_MAX];
	std::string m_player2_texture_list[CLEAR_TEXTURE_MAX];
	std::string m_background_texture_list[BG_TEXTURE_MAX];

	const float BACKGROUND_TEXTURE_SIZE_Y = 1180;	// 背景画像のｙ軸のサイズ
	const int PLAYER_TEXTURE_PARTITION_NUM = 4;		// プレイヤーの画像分割数

	// エフェクトの登録
	const std::string m_clear_effect = "Resource/Texture/Effect/crear_eff.png";
};
