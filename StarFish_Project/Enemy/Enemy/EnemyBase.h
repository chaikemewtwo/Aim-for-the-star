#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../CollisionObject/CircleCollisionObject.h"
#include"../../Map/MapChip/MapChip.h"
#include"../../Player/Player.h"
#include"../State/EnemyStateBase.h"


// 敵の状態識別Id
enum StateId {
	WAIT_ID,			// 待機
	SIDEMOVE_ID,		// 横線移動
	VERTICALMOVE_ID,	// 縦線移動
	ATTACK_READY_ID,	// 攻撃準備
	STATEID_MAX
};

enum EnemyTexture {
	SEAURCHIN_MOVE,
	SELLFISH_WAIT,
	SELLFISH_READY,
	SELLFISH_ATTACK,
	ENEMY_TEXTURE_MAX
};

// 敵基底クラス
class EnemyBase :public CircleCollisionObject{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	virtual StateId StateChangeCheck() = 0;

	virtual void ChangeState(StateBase* state);
	// 敵のインスタンスを返す関数
	virtual EnemyBase* GetInstance();	

	// 各種Getter・setter //
	virtual float GetSpeed();
	virtual int GetPower();			
	// 左右どちらにいるか判定フラグのゲッター
	virtual bool IsLeft();				

	Type GetObjectType()const override {
		return ENEMY;
	}

protected:
	// 画面外に出たらm_is_activをfalseにする関数
	virtual void OutScreenCheck();
	// 敵の位置がプレイヤーの上かをboolで返す関数
	virtual bool IsTopPos();
	// 2体のプレイヤーの、自身とより近い距離を返す関数
	virtual float CalcDistance();//《引数で現在地と目標地をとれるように変更》

	// 変数・定数//
	int m_power;				// 攻撃力
	int m_delete_timer;			// 削除用タイマー
	bool m_no_move;				// 移動するかのフラグ
	bool m_is_left;				// 画面中央から左右どちらにいるかのフラグ
	float m_angle;				// 描画角度
	float m_center;				// 描画頂点
	int m_anim_change_time;		// アニメーションの速度
	int m_max_animation;		// 使用するアニメーション数
	std::string m_texture_list[ENEMY_TEXTURE_MAX];
	std::string m_texture;

	StateBase* m_pstate_base;	// 状態を保存する変数
	MapChip* m_pmap;
	Player* m_pplayer1;
	Player* m_pplayer2;

	const int TEX_PARTITION_NUM2 = 2;	// 画像の分割数　　2分割
	const float TEXTURE_SIZE_X = 0.5f;	// 描画する画像のXサイズ
	const float TEXTURE_SIZE_Y = 0.5f;	// 描画する画像のYサイズ
};
