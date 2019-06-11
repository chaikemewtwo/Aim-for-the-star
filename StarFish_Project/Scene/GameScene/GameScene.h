#pragma once

#include"../SceneBase.h"
#include"../../GameUI/GameUI.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"


class GameMain :public SceneBase {
public:
	GameMain();
	~GameMain() {}

private:
	void Init()override;
	void Update()override;
	void Draw()override;

	// ゲームオーバー時の処理
	bool CheckChangeScene();
	
private:
	D3DXVECTOR2 m_gameover_ui_pos;		// UIの位置
	float m_gameover_ui_speed;			// 移動速度
	float m_gameover_ui_posy_max;		// UIのｙ軸の最大位置

	float m_gameover_scene_change_time; // ゲームオーバー時の遷移までの時間
	float m_scene_change_count_timer;	// 遷移までのカウント

	// ゲームオーバーロゴの登録
	const std::string m_gameover_ui = "Resource/Texture/UI/over_logo.png";
	
	IDirectSoundBuffer8* m_p_main_bgm;			// ゲームシーンBGM
	IDirectSoundBuffer8* m_p_gameover_jingle;	// ゲームオーバージングル

	ObjectManager* m_p_obj_mng;
};
