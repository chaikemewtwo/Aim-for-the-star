#pragma once

#include"../CollisionObject/CircleCollisionObject.h"
#include"PlayerState\PlayerStateBase.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Sound/DirectSound.h"


class Map;

// プレイヤーオブジェクトクラス（自機2体とも）
class Player : public CircleCollisionObject {
public:	
	// 自機1か2かの判断
	// 主にコンストラクタで使用
	enum ID_TYPE {
		STAR_1,
		STAR_2
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

	// スタミナ最大値
	// HACK:UIのパーセンテージ関数をプレイヤーが持つことでこの定数をprivateに置く
	static const int MAX_STAMINA = 1000;

public:
	// コンストラクタ（引数でオレンジくんとピンクちゃんを判別）
	Player(ID_TYPE id);

	// デストラクタ
	~Player() {}

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;

	//-----------------------------------------------------
	// 当たり判定で使用する関数
	// プレイヤー移動量ゲッター
	D3DXVECTOR2 GetMove()const;

	// プレイヤー座標セッター
	void SetPos(D3DXVECTOR2 pos);

	// プレイヤー移動量セッター
	void SetMove(D3DXVECTOR2 move);

	// プレイヤー移動量の加算関数（ヒモ用、仮）
	void AddMove(D3DXVECTOR2 add_move);
	//-----------------------------------------------------

	//-----------------------------------------------------
	// 状態遷移（各State）で使用する関数
	// 状態切り替え
	// 引数:(変更された後の状態)
	void ChangeState(PlayerStateBase* state);

	// アニメーション番号0初期化
	void ResetAnimationCount();

	// 重力負荷
	// 移動量に加算
	void AddGravity();

	// X方向向き変更
	// 引数:(trueで右へ傾く)
	void AngleAdjust(bool is_move_right);

	// 泳ぐ（ジャンプ）
	// 傾いてる向きに移動量を加算
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
	int GetStamina();

	// スタミナ減算
	void DecStamina(int dec_sutamina_num);

	// 生存フラグ無効化
	void EnableDead();
	//-----------------------------------------------------

	// 自機を返す設定をする、CollisionObjectで使用
	Type GetObjectType()const override { 
		return PLAYER;
	}

public:
	bool swim_enable;	// 泳いでるフラグ(泳ぎ状態のときtrue)
	std::string star_texture_name[MAX_TEXTURE_NUM];	// テクスチャ文字列保持
	char imput_button_name[MAX_KEY_NUM];	// 入力キー文字列保持（操作分割のため）

private:
	//-----------------------------------------------------
	// ゲーム内パラメータ用定数
	// 1フレームごとの画面下への移動量、重力負荷に使用
	const float GRAVITY = -1.f;

	// 向き変更時に1フレームごとに傾く角度
	const float ANGLE_ADD = 0.5f;

	// 向き変更時最大角度（ヒトデの頭の向きの左右の最大角度）
	const float MAX_ANGLE = 45.f;

	// プレイヤーの当たり判定の半径
	static const float PLAYER_COLLSION_RADIUS;

	// 泳ぐ際の移動速度
	// この値を1f毎に移動量に加算する
	static const float PLAYER_SPEED;

	// 自機1のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_1_FIRST_POS;

	// 自機2のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_2_FIRST_POS;

	// テクスチャサイズ調整
	static const D3DXVECTOR2 TEXTURE_SIZE_OFFSET;

	// 画像分割
	static const D3DXVECTOR2 TEXTURE_PARTITION;

	// 敵との被弾時に減らされるスタミナ
	static const int DECREASE_STAMINA;
	//-----------------------------------------------------

	// 無敵時間タイマー、未実装
	//void GetDamageTimer();

	// 自機と敵との当たり判定後の処理(点滅させる)
	void HitAction(Type type)override;

	std::string m_player_texture;	// 画像格納用
	D3DXVECTOR2 m_move;				// X、Y方向移動量
	//D3DXVECTOR2 m_dbg_proto_move;	// 仮の移動量（動く前のシュミレーション用、未実装）
	float m_angle;					// 自機画像角度（MAX_ANGLEから-MAX_ANGLE度まで）
	int m_stamina;					// スタミナ
	int m_state_change_timer;		// 状態遷移用タイマー		
	int invisible_count;			// 敵被弾後無敵時間					
	bool m_draw_enable;				// 被弾時点滅用描画切り替え			
	bool m_is_hit;					// 被弾フラグ（まだ未使用）

	
	PlayerStateBase * m_p_state;		// ステート基底クラス					
	IDirectSoundBuffer8* m_p_hit_se;	// 被弾SE
										
	Audio& m_p_audio = Audio::getInterface();	// オーディオインターフェース
};
