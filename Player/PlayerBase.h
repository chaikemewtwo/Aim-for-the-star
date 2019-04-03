#pragma once
#include "../Common/Common.h"

// MEMO:リファクタリングのため自機1と2の操作が同一になっています


class PlayerBase {
public:
	// コンストラクタ
	PlayerBase();
	// デストラクタ
	virtual ~PlayerBase() {}

	// 更新処理
	// HACK：自機2も自機1の操作方法になっているので操作の分離が必要
	void Update();
	
	// 描画処理
	// MEMO:自機2も自機1の画像を使用中
	void Draw();
	
protected:
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
	// プレイヤー状態列挙型
	enum State {
		STATE_NONE,              // null
		STATE_DROP,              // 落下
		STATE_SWIM,				// 泳ぎ
		STATE_STAND_ON_OBJECT,	// オブジェクト上に立つ
		STATE_GET_STUCK,		// 岩張り付き
		STATE_DEATH,			// 死亡
		STATE_MAX_NUM			// 最大値
	};
	//-----------------------------------------------------

	// 関数
	// 重力負荷
	void AddGravity();

	// X方向向き変更
	void AngleAdjust(bool is_move_right);
	

	// 変数
	// プレイヤー座標
	float pos_x,pos_y;

	// X、Y方向移動量
	float move_x, move_y;

	// 移動速度
	float move_speed;

	// 落下速度
	float drop_speed;

	// 自機画像角度
	float character_angle;

	// 挙動のアニメーション番号管理用
	int animation_num;

	// 泳ぎクールタイム計測用
	int swim_interval_count;

private:
	// 泳ぐ（ジャンプ）
	// 傾いてる向きに移動
	void SwimUp();

	// アニメーション番号リセット用（未実装）
	// 状態を切り替える際に使いたい
	//void AnimationReset();
};
