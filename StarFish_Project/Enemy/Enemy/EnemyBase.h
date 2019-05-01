﻿#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../State/EnemyStateBase.h"
#include"../State/EnemyWaitState.h"
#include"../../GameObject/Object/Object.h"

// 敵の種類
enum EnemyTypeId {
	SeaUrchinId,		// ウニ
	SellFishId,			// ほら貝
	NapoleonFishId,		// ナポレオンフィッシュ
	//EnemyTypeMax		// 敵種の最大数
};

// 敵の状態識別Id
enum StateId {
	WaitId,				// 待機
	SideMoveId,			// 横線移動
	VerticalMoveId		// 縦線移動
};


// 敵基底クラス
class EnemyBase :public Object{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	virtual void Init() = 0;						// 初期化《変更予定》
	virtual void ChangeState(StateBase* state) = 0;	// 遷移

	// 画面外に出たらm_is_deadをtrueにする関数
	virtual void  OutScreen();
	// アニメーション操作関数
	virtual void AnimationDraw(int text_x_num, int text_y_num, int anim_speed);

	// 位置座標のゲッター、セッター
	virtual float GetPosX();
	virtual float GetPosY();

	virtual void SetPosX(float x);
	virtual void SetPosY(float y);

	// 速度のゲッター
	virtual float GetSpeed();

	// 攻撃力のゲッター
	virtual int GetPower();

	// 移動するかの判定フラグのゲッター
	virtual bool NoMove();

	virtual bool IsLeft();

	// 削除フラグのゲッター
	virtual bool IsActive();

	// 敵種類のゲッター
	virtual int GetEnemyType();

	// 現在のStateIdのセッター
	virtual void SetStateId(StateId state_id);

protected:
	int m_power;			// 攻撃力
	int m_delete_timer;		// 削除用タイマー
	bool m_no_move;			// 移動するかのフラグ
	bool m_is_left;			// 画面中央から左右どちらにいるかのフラグ
	bool m_is_active;		// 削除フラグ	《削除予定》
	int m_enemy_type;		// 敵の種類
	int m_animation_num;	// 現在のアニメーション画像番号
	int m_animation_speed;	// アニメーションの速度
	int m_animation_timer;	// アニメーションのカウント用変数
	float m_angle;			// 描画角度
	int m_stateid;			// 現在のStateId

	const int TEXT_PARTITION_NUM2 = 2;	// 画像の分割数　　2分割
	const int NEED_PARTITION_NUM1 = 1;	// 使用する分割列　1列分
	const float TEXTURE_SIZE_X = 0.5f;	// 描画する画像のXサイズ
	const float TEXTURE_SIZE_Y = 0.5f;	// 描画する画像のYサイズ
};
