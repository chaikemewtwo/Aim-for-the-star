#pragma once

#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Input/KeyBord.h"
#include"../Lib/Input/GamePad.h"
#include"../CollisionObject/CircleCollisionObject.h"
#include"PlayerState\PlayerStateBase.h"


class Map;

class Player : public CircleCollisionObject {
public:	
	// 自機1か2かの判断（主にコンストラクタで使用）
	enum ID_TYPE {
		STAR_1,
		STAR_2
	};

	// 入力キー（後々操作入力をまとめたクラスを作成する）
	enum IMPUT_KEY {
		LEFT_KEY,		// 左キー
		RIGHT_KEY,		// 右キー
		SWIM_KEY,		// 泳ぐキー
		PULL_ROPE_KEY,	// ロープ引っ張りキー

		MAX_KEY_NUM		// 最大値
	};

	// 状態画像切り替え定数
	enum PLAYER_STATE_TEXTURE {
		WAIT_TEXTURE,
		STANDING_WAIT_TEXTURE,
		SWIM_TEXTURE,
		DEATH_TEXTURE,

		MAX_TEXTURE_NUM
	};

	// スタミナ最大値
	const int MAX_STAMINA = 1000;

	// 泳いでるフラグ(泳ぎ状態のときtrue)
	bool swim_enable;

	// 入力キー文字列保持（操作分割のため）
	char imput_button_name[MAX_KEY_NUM];

	// テクスチャ文字列保持
	std::string star_texture_name[MAX_TEXTURE_NUM];

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
	void ChangeState(PlayerStateBase* state);

	// アニメーション番号0初期化
	void ResetAnimationNumber();

	// 重力負荷
	void AddGravity();

	// X方向向き変更
	void AngleAdjust(bool is_move_right);

	// 泳ぐ（ジャンプ）、傾いてる向きに移動
	void SwimUp();

	// 状態画像セッター
	void SetPlayerTexture(std::string new_player_texture);

	// 状態遷移タイマーゲッター
	int GetStateChangeTimer();

	// 状態遷移タイマー0初期化
	void ResetStateChangeTimer();

	// 状態遷移タイマーインクリメント
	void AddStateChangeTimer();

	// スタミナゲッター
	int GetStamina();

	// スタミナ減算
	void DecStamina(int dec_sutamina_num);

	// 死亡フラグ立てる
	void EnableDead();
	//-----------------------------------------------------

	// MEMO:CollisionObjectで必要なので追加
	// 自機を返す設定をする
	Type GetObjectType()const override { 
		return PLAYER;
	}
		

private:
	//-----------------------------------------------------
	// ゲーム内パラメータ用定数
	// 1フレームごとの画面下への移動量、重力負荷に使用
	const float GRAVITY = -1.f;

	// 向き変更時に1フレームごとに傾く角度
	const float ANGLE_ADD = 0.5f;

	// 向き変更時最大角度（ヒトデの頭の向きの左右の最大角度）
	const float MAX_ANGLE = 45.f;
	//-----------------------------------------------------

	// 無敵時間タイマー、未実装
	//void GetDamageTimer();

	// 自機と敵との当たり判定後の処理(点滅させる)
	void HitAction(Type type)override;

	// 画像格納用
	std::string m_player_texture;

	// X、Y方向移動量
	D3DXVECTOR2 m_move;

	// 自機画像角度（MAX_ANGLEから-MAX_ANGLE度まで）
	float m_angle;

	// 状態遷移用タイマー
	int m_state_change_timer;

	// ステート基底クラスのインスタンス
	PlayerStateBase * m_state;

	// スタミナ
	int m_stamina;

	// 敵被弾後無敵時間
	int invisible_count;

	// 被弾時点滅用描画切り替え
	bool m_draw_enable;

	// 仮の移動量（動く前のシュミレーション用）
	D3DXVECTOR2 m_proto_move;

	// 被弾フラグ（まだ未使用）
	bool m_is_hit;
};
