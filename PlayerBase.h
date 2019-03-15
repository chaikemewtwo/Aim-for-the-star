#pragma once
#include "Common.h"


// テクスチャサイズ調整X座標用
const float TEXTURE_SIZE_X = 1.f;
// テクスチャサイズ調整Y座標用
const float TEXTURE_SIZE_Y = 1.f;

// 重力負荷
const float GRAVITY = 0.01f;
// X方向の移動量（左右移動）
const float X_ADD = 2.f;
// Y方向の移動量（ジャンプ）
const float Y_ADD = -1.5f;
// 泳ぎインターバル
const float SWIM_INTERVAL = 90.f;

class PlayerBase {
public:
	// コンストラクタ
	PlayerBase();
	// デストラクタ
	virtual ~PlayerBase() {}

	// 更新処理
	virtual void Update() = 0;
	// HACK：自機１、２の処理が似ているので基底クラスでまとめたい

	// 描画処理
	virtual void Draw() = 0;
	
protected:
	// 自機操作
	//virtual void Control() = 0;

	// 重力負荷
	void AddGravity();

	// 泳ぐ（ジャンプ）
	void SwimUp();

	// X方向移動、TRUEで右へ移動
	void XMove(bool move_right);
	
	// プレイヤーX座標
	float pos_x;
	// プレイヤーY座標
	float pos_y;
	// HACK：pos_x,yはprivateにしたい
	float speed;

	float interval_count;
private:
	
};
