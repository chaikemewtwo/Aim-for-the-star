﻿#pragma once
#include "../../Common/Common.h"

// MEMO:リファクタリングのため自機1と2の操作が同一になっています

class PlayerBase {
public:
	//-----------------------------------------------------
	enum STATE {
		WAIT,
		SWIM,
		STANDING_WAIT,
		DAMAGE,
		DEATH,
		MAX_STATE_NUMBER
	};
	//-----------------------------------------------------

	// 関数
	// コンストラクタ
	PlayerBase();

	// 仮想デストラクタ
	virtual ~PlayerBase() {}

	// 更新処理
	// HACK：自機2も自機1の操作方法になっているので操作の分離が必要
	void Update();
	
	// 描画処理
	// MEMO:自機2も自機1の画像を使用中、自機2の画像が完成次第変更する
	void Draw();

	// ステート変更
	void ChangeState(STATE* state);

	// アニメーション番号上書き（セッター）
	void SetAnimationNumber(int new_animation_number);
	
protected:

	//-----------------------------------------------------
	// ゲーム内パラメータ用定数
	// 重力負荷
	const float GRAVITY = 1.f;

	// 角度変換
	const float ANGLE_ADD = 0.5f;

	// 泳ぎインターバル
	const int SWIM_INTERVAL = 96;

	// 向き変更時最大角度
	const float MAX_ANGLE = 45.f;

	// 泳ぎアニメーション補助用
	const int SWIM_ANIMATION_SUPPORT_NUMBER = 6;
	//-----------------------------------------------------

	//-----------------------------------------------------
	// 描画調整用定数
	// テクスチャサイズ調整X座標用
	const float TEXTURE_SIZE_X = 0.25f;

	// テクスチャサイズ調整Y座標用
	const float TEXTURE_SIZE_Y = 0.25f;

	// 分割画像X枚数
	const int TEXTURE_PARTITION_X_NUMBER = 4;

	// 分割画像Y枚数
	const int TEXTURE_PARTITION_Y_NUMBER = 4;
	//-----------------------------------------------------



	// 関数
	// 重力負荷
	void AddGravity();

	// X方向向き変更
	void AngleAdjust(bool is_move_right);
	

	// 変数
	// プレイヤー座標
	float m_pos_x, m_pos_y;

	// 画像格納用
	// HACK:配列の方がいいかも
	std::string m_player_texture/*[MAX_STATE_NUMBER]*/;

	// X、Y方向移動量
	float m_move_x, m_move_y;

	// 移動速度
	float m_move_speed;

	// 自機画像角度
	float m_character_angle;

	// 挙動のアニメーション番号管理用
	int m_animation_number;

	// 泳ぎクールタイム計測用
	// HACK:Stateパターン内で管理する
	int m_swim_interval_count;

private:
	// 関数
	// 泳ぐ（ジャンプ）、傾いてる向きに移動
	void SwimUp();

	// ステートベースインスタンス
	STATE m_state;
};