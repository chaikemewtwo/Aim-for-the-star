#pragma once

#include<string>
#include"../../Lib/Window/Window.h"
#include"../SceneBase.h"


class Clear :public SceneBase {
public:
	Clear();
	~Clear() {}

private:
	enum BackGroundTex {
		TEXTURE_1,
		TEXTURE_2,
		TEXTURE_3,
		BACKGROUND_TEXTURE_MAX
	};

	enum PlayerClearTex {
		FLY_TEXTURE,
		CLEAR_POSE_TEXTURE,
		CLEAR_TEXTURE_MAX
	};


	void Init()override;
	void Update()override;
	void Draw()override;

	// プレイヤーのアニメーション処理
	void ChangePlayerAnimation();
	// エフェクトのアニメーション処理
	void ChangeEffectAnimation();
	void PlayerMove();
	void BackGroundMove();
	void ClearUiSizeChange();
	
private:
	int m_scene_change_count_timer;		// 遷移までの時間カウント用
	int m_scene_change_time;			// 遷移用の時間

	//　プレイヤー　//
	D3DXVECTOR2 m_player1_pos;			// 位置１
	D3DXVECTOR2 m_player2_pos;			// 位置２
	float m_player_move_speed;			// 移動速度

	int m_player_animation_timer;		// アニメーション時間カウント用
	int m_player_animation_change_time;	// アニメーションの遷移時間
	int m_player_animation_num;			// アニメーション番号
	int m_player_animation_max;			// アニメーション数
	bool m_player_animation_finish;		// アニメーション完了フラグ

	// 画像用変数と画像リスト
	std::string m_player1_texture;
	std::string m_player2_texture;
	std::string m_player1_texture_list[CLEAR_TEXTURE_MAX];
	std::string m_player2_texture_list[CLEAR_TEXTURE_MAX];

	const float PLAYER_FINISH_POS_Y = 750;			// プレイヤーの最終位置
	const float PLAYER_DECELERATION_POS_Y = 950;	// プレイヤーの減速位置

	const int PLAYER_CLEARPOSE_START_NUM = 6;		// ポーズの開始番号
	const int PLAYER_REPEAT_ANIMATION_LAST_NUM = 13;// アニメーションの繰り返し位置の番号（終わり）
	const int PLAYER_REPEAT_ANIMATION_START_NUM = 5;// アニメーションの繰り返し位置の番号（始まり） 
	const int PLAYER_TEXTURE_PARTITION_NUM = 4;		// プレイヤーの画像分割数

	//　背景　//
	D3DXVECTOR2 m_background1_pos;		// 位置１
	D3DXVECTOR2 m_background2_pos;		// 位置２
	float m_background_move_speed;		// 移動速度
	bool m_is_background_move;			// 背景を動かすフラグ

	// 画像用変数と画像リスト
	std::string m_background_texture1;
	std::string m_background_texture2;
	std::string m_background_texture_list[BACKGROUND_TEXTURE_MAX];

	const float BACKGROUND_TEXTURE_SIZE_Y = 1180;	// 背景画像のｙ軸のサイズ

	//　エフェクト　//
	int m_effect_animation_num;			// アニメーション番号
	int m_effect_animation_max;			// アニメション数
	int m_effect_animation_timer;		// アニメーションの時間カウント用
	int m_effect_animation_change_time;// アニメーションの遷移時間

	const int EFFECT_TEXTURE_PARTITION_NUM = 4;		// エフェクトの画像分割数

	// エフェクトの登録
	const std::string m_clear_effect = "Resource/Texture/Effect/crear_eff.png";

	//　成功UI　//
	D3DXVECTOR2 m_clear_ui_pos;			// 座標
	float m_clear_ui_size;				// サイズ
	float m_clear_ui_size_change_speed;	// サイズ変更の速度
	bool m_is_clear_ui_size_max;		// 描画サイズが本来のサイズかどうか

	const float CLEAR_UI_MIN_SIZE = 0.9f;			// UIの最小サイズ
	// UIの登録
	const std::string m_clear_ui_texture = "Resource/Texture/UI/clear_logo.png";

	// クリア時のサウンド
	IDirectSoundBuffer8* m_fly_sound;
	IDirectSoundBuffer8* m_effect_sound;
};
