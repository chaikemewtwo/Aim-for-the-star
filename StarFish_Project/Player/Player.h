#pragma once

#include"../CollisionObject/CircleCollisionObject.h"
#include"PlayerState\PlayerStateBase.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Sound/DirectSound.h"


class Map;

// HACK:順序を決め並び替えをする　19/06/14

// プレイヤーオブジェクトクラス（自機2体とも）
class Player : public CircleCollisionObject {
public:	
	// 自機1か2かの判断
	// 主にコンストラクタで使用
	enum ID_TYPE {
		STAR_1,
		STAR_2,
		MAX_TYPE
	};

	// 入力キーデータ（後々操作入力をまとめたクラスを作成する）
	// プレイヤーのコンストラクタで初期化し状態クラスで使用
	enum IMPUT_KEY {
		LEFT_KEY,		
		RIGHT_KEY,		
		SWIM_KEY,		
		PULL_ROPE_KEY,	

		MAX_KEY_NUM		
	};

	// 状態画像データ
	// プレイヤーのコンストラクタで初期化し状態クラスで使用
	enum PLAYER_STATE_TEXTURE {
		WAIT_TEXTURE,			
		STANDING_WAIT_TEXTURE,	
		SWIM_TEXTURE,			
		DEATH_TEXTURE,			

		MAX_TEXTURE_NUM			
	};

public:
	// コンストラクタ
	// 引数でオレンジくんとピンクちゃんを判別しています
	Player(ID_TYPE id);

	// デストラクタ
	~Player() {}

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;

	//-----------------------------------------------------
	// 当たり判定で使用する関数

	// プレイヤー座標セッター
	void SetPos(D3DXVECTOR2 pos);

	// プレイヤー移動量ゲッター
	D3DXVECTOR2 GetMove()const;

	// プレイヤー移動量セッター
	void SetMove(D3DXVECTOR2 move);

	void SetMoveX(float move_x) {
		m_move.x = move_x;
	}

	// プレイヤー移動量の加算関数（ヒモ用、仮）
	void AddMove(D3DXVECTOR2 add_move);
	//-----------------------------------------------------

	//-----------------------------------------------------
	// 状態遷移（各State）で使用する関数

	// 状態切り替え
	// 各StateのInitも行う
	// 引数:(変更された後の状態)
	void ChangeState(PlayerStateBase* state);

	// アニメーション番号0初期化
	void ResetAnimationCount();

	// 重力負荷
	// 重力を移動量に加算
	void AddGravity();

	// X方向向き変更
	// -MAX_ANGLEからMAX_ANGLEまで傾けることができます
	// 引数:(trueで右へ傾く)
	void AngleAdjust(bool is_move_right);

	// 泳ぐ（ジャンプ）
	// 1fごとに傾いてる向きに移動量を加算
	void SwimUp();

	// 状態画像セッター
	void SetPlayerTexture(std::string new_player_texture);

	// 状態遷移タイマーゲッター
	int GetStateChangeTimer();

	// 状態遷移タイマー0初期化
	void ResetStateChangeTimer();

	// 状態遷移タイマー加算
	void AddStateChangeTimer();

	// スタミナゲッター
	float GetStamina();

	// 泳ぐフラグゲッター
	bool SwimEnable();

	// 泳ぐフラグセッター
	void SetSwimEnable(bool new_swim_enable);

	// スタミナ減算
	void DecStamina(float dec_sutamina_num);

	// 現在のスタミナの比率を返す
	// MAX_STAMINAを1.fとしたときのm_staminaの割合
	float StaminaParcentage();

	// 生存フラグ無効化
	void EnableDead();
	//-----------------------------------------------------

	// 自機を返す設定をする
	// CollisionObjectで使用
	Type GetObjectType()const override { 
		return PLAYER;
	}

public:
	// HACK:public領域の変数をなくす　19/06/14	
	std::string star_texture_list[MAX_TEXTURE_NUM];	// テクスチャ文字列保持
	char imput_button_list[MAX_KEY_NUM];	// 入力キー文字列保持（2体の操作分割のため）

private:
	// 重力
	// 1フレームごとの画面下への移動量
	static const float GRAVITY;

	// 向き変更時に1フレームごとに傾く角度
	static const float ANGLE_ADD;

	// 向き変更時最大角度
	// テクスチャの向きの左右の最大角度
	static const float MAX_ANGLE;

	// 当たり判定の大きさ
	// この値が当たり判定の円の半径です
	static const float PLAYER_COLLSION_RADIUS;

	// 泳ぐ際の移動速度
	// この値を1fごとに移動量に加算します
	static const float PLAYER_SPEED;

	// 自機1のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_1_FIRST_POS;

	// 自機2のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_2_FIRST_POS;

	// テクスチャサイズ調整
	static const D3DXVECTOR2 TEXTURE_SIZE_OFFSET;

	// 画像分割
	// 使用例:4*4サイズの統合画像ならこの値は{4.f,4.f}
	static const D3DXVECTOR2 TEXTURE_PARTITION;

	// スタミナ最大値
	static const float MAX_STAMINA;

	// 敵との被弾時に減らされるスタミナ
	static const float DECREASE_STAMINA;

	// 敵と被弾後の無敵時間カウントの最大値
	// このフレーム数だけ無敵時間が行われる
	static const float MAX_INVISIBLE_COUNT;

private:
	// 無敵時間タイマー、未実装
	// (点滅させる)
	void DBGGetDamageTimer();

	// 自機との当たり判定後の処理
	// 基本的にEnemyとの当たりで使用する
	// 引数は当たりたいオブジェクトの種類
	void HitAction(Type type)override;

private:
	std::string m_player_texture;	// 画像格納用
	D3DXVECTOR2 m_move;				// X、Y方向移動量
	float m_angle;					// 自機画像角度（MAX_ANGLEから-MAX_ANGLE度まで）
	float m_stamina;				// スタミナ
	int m_state_change_timer;		// 状態遷移用タイマー		
	int m_invisible_count;			// 敵と被弾後の無敵時間カウント					
	bool m_draw_enable;				// 被弾時点滅用描画切り替え			
	bool m_invisible_count_start;					// 被弾フラグ（まだ未使用）
	bool m_swim_enable;				// 泳いでるフラグ(泳ぎ状態のときtrue)

	
	PlayerStateBase* m_p_state;		// ステート基底クラス					
	IDirectSoundBuffer8* m_p_hit_se;	// 被弾SE
										
	Audio& m_p_audio = Audio::getInterface();	// オーディオインターフェース
};
