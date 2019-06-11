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


// 敵基底クラス
class EnemyBase :public CircleCollisionObject{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	// 各遷移条件をチェックし、遷移先のStateIdを返す
	virtual StateId StateChangeCheck() = 0;

	// 敵のインスタンスを返す
	virtual EnemyBase* GetInstance();	

	// 引数で指定したStateに遷移
	void ChangeState(StateBase* state);

	// 速度のゲッター
	float GetSpeed();

	//int GetPower();
	
	// 画面の左右どちらかのフラグのゲッター
	bool IsLeft();				

	// オブジェクトタイプのゲッター
	Type GetObjectType()const override {
		return ENEMY;
	}

protected:
	enum EnemyTexture {
		SEAURCHIN_MOVE,		// ウニ画像
		SELLFISH_WAIT,		// ほら貝の待機画像
		SELLFISH_READY,		// ほら貝の攻撃前画像
		SELLFISH_ATTACK,	// ほら貝の攻撃画像
		ENEMY_TEXTURE_MAX
	};


	// 画面外に出たらm_is_activをfalseにする関数
	void OutScreenCheck();

	// 自身の位置がプレイヤーの上下どちらかを判定する
	bool IsTopPos();

	// 2体のプレイヤーの、自身とより近い距離を正の数で返す
	D3DXVECTOR2 CalcDistance();

protected:
	int m_power;				// 攻撃力
	int m_delete_timer;			// 削除用タイマー
	bool m_can_move;			// 移動するかのフラグ
	bool m_is_left;				// 画面中央から左右どちらにいるかのフラグ

	float m_angle;				// 描画角度
	float m_center;				// 描画頂点
	int m_anim_change_time;		// 1コマ分の画像の時間
	int m_max_animation;		// 使用するアニメーション数

	std::string m_enemy_texture;// 敵の画像変数
	std::string m_texture_list[ENEMY_TEXTURE_MAX];	// 敵の画像リスト
	

	// 画像の分割数　　2分割
	const int TEX_PARTITION_NUM2 = 2;	
	// 描画する画像のXサイズ
	const float TEXTURE_SIZE_X = 0.5f;	
	// 描画する画像のYサイズ
	const float TEXTURE_SIZE_Y = 0.5f;	

	StateBase* m_p_state_base;	// 状態を保存する変数
	Map* m_p_map;
	Player* m_p_player[2];
};
