#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../CollisionObject/CircleCollisionObject.h"
#include"../../Map/MapChip/MapChip.h"
#include"../State/EnemyStateBase.h"


// 敵の種類
enum EnemyTypeId {
	SEAURCHIN_ID,		// ウニ
	SELLFISH_ID,		// ほら貝
	NAPOLEONFISH_ID,	// ナポレオンフィッシュ
	ENEMY_TYPE_MAX
};

// 敵の状態識別Id
enum StateId {
	WAIT_ID,			// 待機
	SIDEMOVE_ID,		// 横線移動
	VERTICALMOVE_ID,	// 縦線移動
	ATTACK_READY_ID,	// 攻撃準備
	STATEID_MAX
};


// 敵基底クラス
class EnemyBase :public CircleCollisionObject{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	virtual void ChangeState(StateBase* state);
	// 画面外に出たらm_is_deadをtrueにする関数
	virtual void  OutScreen();
	// 敵のインスタンスを返す関数
	virtual EnemyBase* GetInstance();

	// 各種ゲッター、セッター
	virtual float GetSpeed();
	virtual int GetPower();
	// 移動するかの判定フラグのゲッター
	virtual bool NoMove();
	// 左右どちらにいるか判定フラグのゲッター
	virtual bool IsLeft();
	virtual int GetEnemyType();
	virtual void SetStateId(StateId state_id);

	Type GetObjectType()const override {
		return ENEMY;
	}

protected:
	int m_power;				// 攻撃力
	int m_delete_timer;			// 削除用タイマー
	bool m_no_move;				// 移動するかのフラグ
	bool m_is_left;				// 画面中央から左右どちらにいるかのフラグ
	EnemyTypeId m_enemy_type;	// 敵の種類
	StateId m_stateid;			// 現在のStateId
	float m_angle;				// 描画角度
	int m_anim_change_time;		// アニメーションの速度
	int m_max_animation;		// 使用するアニメーション数

	StateBase* m_pstate_base;	// 状態を保存する変数
	MapChip* m_pmap;

	const int TEX_PARTITION_NUM2 = 2;	// 画像の分割数　　2分割
	const float TEXTURE_SIZE_X = 0.5f;	// 描画する画像のXサイズ
	const float TEXTURE_SIZE_Y = 0.5f;	// 描画する画像のYサイズ
};
