#pragma once
#include "../Common/Common.h"

// MEMO:簡略化のため自機1と2の操作が同一になっています

// テクスチャサイズ調整X座標用
const float TEXTURE_SIZE_X = 0.25f;
// テクスチャサイズ調整Y座標用
const float TEXTURE_SIZE_Y = 0.25f;

// 重力負荷
const float GRAVITY = 0.01f;
// X方向の移動量（左右移動）
const float X_ADD = 1.f;
// Y方向の移動量（ジャンプ）
const float Y_ADD = -2.f;
// 泳ぎインターバル
const float SWIM_INTERVAL = 96.f;
// 向き変更時最大角度
const float MAX_ANGLE = 45.f;

class PlayerBase {
public:
	// コンストラクタ
	PlayerBase();
	// デストラクタ
	virtual ~PlayerBase() {}

	// 更新処理
	void Update();
	// HACK：自機2も自機1の操作方法になっているので操作の分離が必要

	// 描画処理
	void Draw();
	// MEMO:自機2も自機1の画像を使用中
	
protected:
	// 重力負荷
	void AddGravity();

	// 泳ぐ（ジャンプ）
	// HACK:向いている方向に泳ぎたい
	void SwimUp();

	// X方向向き変更
	void AngleAdjust(bool is_move_right);
	
	// プレイヤーX座標
	float pos_x;
	// プレイヤーY座標
	float pos_y;
	// HACK：pos_x,yはprivateにしたい

	// 落下速度
	float drop_speed;

	// 自機画像角度
	float star_angle;

	// 泳ぎアニメーション
	int swim_animetion_num;

	// 泳ぎクールタイム計測用
	int swim_interval_count;

private:
	
};
