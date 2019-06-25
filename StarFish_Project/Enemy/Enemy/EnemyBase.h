﻿#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Window/Window.h"
#include"../../CollisionObject/CircleCollisionObject.h"
#include"../../Map/MapChip/MapChip.h"
#include"../../Player/Player.h"
#include"../EnemyState/EnemyStateBase.h"


// 敵の状態識別Id
enum StateId {
	WAIT_ID,			// 待機
	SIDEMOVE_ID,		// 横線移動
	VERTICALMOVE_ID,	// 縦線移動
	PATROL_ID,			// 徘徊移動
	ATTACK_READY_ID,	// 攻撃準備
	CHASE_ID,			// 追跡処理
	STATEID_MAX
};


// 敵基底クラス
class EnemyBase :public CircleCollisionObject{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}


	// 各遷移条件をチェックし、遷移先のStateIdを返す
	virtual StateId CheckChangeState() = 0;


	/*
	各Stateで実行する挙動
	敵ごとに挙動が違う場合は、派生先で再定義すること
	*/
	// 横移動
	virtual void SideMove();

	// 縦移動
	virtual void VerticalMove();

	// 巡回
	virtual void Patrol();

	// 追跡
	virtual void Chase();


	// 敵のインスタンスを返す
	EnemyBase* GetInstance();	

	// 引数で指定したStateに遷移
	void ChangeState(StateBase* state);

	// 速度のゲッター
	float GetSpeed();
	
	// 画面の左右どちらかのフラグのゲッター
	bool IsLeft();

	// オブジェクトタイプのゲッター
	Type GetObjectType()const override {
		return Type::ENEMY;
	}

protected:
	enum EnemyTexture {
		SEAURCHIN_MOVE,		// ウニ画像
		SELLFISH_WAIT,		// ほら貝の待機画像
		SELLFISH_READY,		// ほら貝の攻撃前画像
		SELLFISH_ATTACK,	// ほら貝の攻撃画像
		NAPOREONFISH_MOVE,	// メガネモチノウオの移動画像
		NAPOREONFISH_ATTACK,// メガネモチノウオの攻撃画像
		ENEMY_TEXTURE_MAX
	};


	// 画面外に出たらm_is_activをfalseにする関数
	void CheckEnemyActiv();

	// プレイヤーの位置を受け取り、敵自身と指定のプレイヤーとの距離を返す
	/*
	プレイヤーが２機いるので、引数でどちらかの座標を入れる
	例：CalcDistanceToPlayer(m_p_player[1]->GetPos());
	*/
	D3DXVECTOR2 CalcDistanceToPlayer(const D3DXVECTOR2& target_pos);

	// 自身の位置がプレイヤーの上下どちらかを判定する
	bool IsTopPos();

protected:
	int m_delete_timer;			// 削除用タイマー
	bool m_can_move;			// 移動するかのフラグ
	bool m_is_left;				// 左右どちら向きかのフラグ
	D3DXVECTOR2 m_target_pos;	// 追跡するターゲットの座標
	float m_sin_count;			// Sin波のカウント用

	float m_angle;				// 描画角度
	float m_center;				// 描画頂点
	int m_anim_change_time;		// 1コマ分の画像の時間
	int m_max_animation;		// 使用するアニメーション数

	std::string m_enemy_texture;// 敵の画像変数
	std::string m_texture_list[EnemyTexture::ENEMY_TEXTURE_MAX];	// 敵の画像リスト
	
	// Sin波の最大移動量
	const float SINCURVE_COUNT_MAX = 300;
	// 画面のｙ軸の中心
	const float WINDOW_CENTER_LINE = Window::WIDTH / 2;

	// 画像の分割数　　2分割
	const int TEX_PARTITION_NUM2 = 2;	
	// 描画する画像のXサイズ
	const float TEXTURE_SIZE_X = 0.5f;	
	// 描画する画像のYサイズ
	const float TEXTURE_SIZE_Y = 0.5f;	

	// 追跡範囲の距離
	static const int CHASE_RANGE = 150;
	// 攻撃範囲の距離
	static const int ATTACK_RANGE = 200;
	// 攻撃前の準備状態の範囲距離
	static const int ATTACK_READY_RANGE = 350;

	StateBase* m_p_state_base;	// 状態を保存する変数
	Map* m_p_map;
	Player* m_p_player[2];
};

/*
《Enemy挙動》
	・State全体の整理（コメントアウト部分とか不要なもの）
	・Patrolを左右で計算変える（左なら+、右なら-）
	・コメント入れる
	・Patrol範囲を調整

《メガネ》
	・画像の追加
	・画像の切り替え
	・索敵の確認（左右逆転時）

《その他Enemy》
	・画像の反転処理の反映
	・EnemyManagerのDraw関数の削除
*/
