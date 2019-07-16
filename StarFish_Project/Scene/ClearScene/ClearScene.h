#pragma once

#include<string>
#include"../../Lib/Window/Window.h"
#include"../SceneBase.h"


// クリアシーンクラス
class Clear :public SceneBase {
public:
	Clear();
	~Clear() {}

private:
	// 背景画像ID
	enum BackGroundTex {
		TEXTURE_1,
		TEXTURE_2,
		TEXTURE_3,
		BACKGROUND_TEXTURE_MAX
	};

	// プレイヤー画像ID
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
	
	// クリアシーン内のプレイヤー移動
	void MovePlayer();
	
	// クリアシーン内の背景スクロール
	void ScrollBackGround();
	
	// クリアUIのサイズ変更
	void SizeChangeClearUi();
	
private:
	int m_scene_change_count_timer;		// 遷移までの時間カウント用
	int m_scene_change_time;			// 遷移用の時間

	//　プレイヤー　//
	D3DXVECTOR2 m_player1_pos;			// プレイヤー1の座標
	D3DXVECTOR2 m_player2_pos;			// プレイヤー2の座標
	float m_player_move_speed;			// 移動速度

	int m_player_animation_timer;		// アニメーション時間カウント用
	int m_player_animation_change_time;	// アニメーションの遷移時間
	int m_player_animation_num;			// アニメーション番号
	int m_player_animation_max;			// アニメーション数
	bool m_player_animation_finish;		// アニメーション完了フラグ

	// 画像変数と画像リスト
	std::string m_player1_texture;
	std::string m_player2_texture;
	std::string m_player1_texture_list[CLEAR_TEXTURE_MAX];
	std::string m_player2_texture_list[CLEAR_TEXTURE_MAX];

	// プレイヤーの最終位置
	const float PLAYER_FINISH_POS_Y = 750;			
	// プレイヤーの減速位置
	const float PLAYER_DECELERATION_POS_Y = 950;	
	// ポージングの開始番号
	const int PLAYER_CLEARPOSE_START_NUM = 6;		
	// アニメーションの繰り返し位置の番号（終わり）
	const int PLAYER_REPEAT_ANIMATION_LAST_NUM = 13;
	// アニメーションの繰り返し位置の番号（始まり） 
	const int PLAYER_REPEAT_ANIMATION_START_NUM = 5;
	// プレイヤーの画像分割数
	const int PLAYER_TEXTURE_PARTITION_NUM = 4;		


	//　背景　//
	D3DXVECTOR2 m_background1_pos;		// 画像1の座標
	D3DXVECTOR2 m_background2_pos;		// 画像2の座標
	float m_background_move_speed;		// 移動速度
	bool m_can_background_move;			// 背景を動かすフラグ

	// 画像用変数と画像リスト
	std::string m_background_texture1;
	std::string m_background_texture2;
	std::string m_background_texture_list[BACKGROUND_TEXTURE_MAX];

	// 背景画像のｙ軸のサイズ
	const float BACKGROUND_TEXTURE_SIZE_Y = 1180;	


	//　エフェクト　//
	int m_effect_animation_num;			// アニメーション番号
	int m_effect_animation_max;			// アニメション数
	int m_effect_animation_timer;		// アニメーションの時間カウント用
	int m_effect_animation_change_time;	// アニメーションの遷移時間

	// エフェクトの画像分割数
	const int EFFECT_TEXTURE_PARTITION_NUM = 4;		
	// エフェクトの登録
	const std::string m_clear_effect = "Resource/Texture/Effect/crear_eff.png";


	//　成功UI　//
	D3DXVECTOR2 m_clear_ui_pos;			// 座標
	float m_clear_ui_size;				// サイズ
	float m_clear_ui_size_change_speed;	// サイズ変更の速度
	bool m_is_clear_ui_size_max;		// 描画サイズが本来のサイズかどうか

	// UIの最小サイズ
	const float CLEAR_UI_SIZE_MIN = 0.9f;	
	// UIの最大サイズ
	const float CLEAR_UI_SIZE_MAX = 1.f;

	// UIの登録
	const std::string m_clear_ui_texture = "Resource/Texture/UI/clear_logo.png";

	IDirectSoundBuffer8* m_p_fly_sound;		// プレイヤーの飛ぶサウンド
	IDirectSoundBuffer8* m_p_effect_sound;	// 星のエフェクトサウンド
};
