#pragma once
#include"../CollisionObject/CircleCollisionObject.h"
#include"PlayerState\PlayerStateBase.h"
#include "../../GameInput/GameInput.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Sound/DirectSound.h"


class Map;

// HACK:順序を決め並び替えをする　19/06/14

// プレイヤーオブジェクトクラス（自機2体共通）
class Player : public CircleCollisionObject {
public:	
	// 自機1か2かの判断
	// 主にコンストラクタで使用
	enum ID_TYPE {
		STAR_1,
		STAR_2,
		MAX_TYPE
	};

	enum STAR_INPUT {
		KEY_LEFT,
		KEY_RIGHT,
		KEY_SWIM,
		STAR_KEY_MAX
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
	// 引数で自機1と自機2を判別しています
	Player(ID_TYPE id, D3DXVECTOR2 first_pos);

	// デストラクタ
	~Player() {}

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;

	// インスタンス取得
	Player* GetInstance();
	//-----------------------------------------------------
	// 当たり判定で使用する関数

	// プレイヤー移動量ゲッター
	D3DXVECTOR2 GetMove()const;

	// プレイヤー移動量セッター
	void SetMove(D3DXVECTOR2 move);

	// プレイヤー移動量の加算関数（ヒモ用、仮）
	void AddMove(D3DXVECTOR2 add_move);
	//-----------------------------------------------------

	//-----------------------------------------------------
	// 各Stateで使用する関数

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
	// 向き変更が可能なStateでキー入力を受け取りこの関数を呼び出します
	// 引数:(trueで右へ傾く)
	void AngleAdjust(bool is_move_right);

	// 泳ぐ（ジャンプ）
	// 1fごとに傾いてる向きに移動量を加算
	void SwimUp();

	// 状態画像セッター
	void SetPlayerTexture(PLAYER_STATE_TEXTURE new_state_texture);

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
	// 戻り値:MAX_STAMINAを1.fとしたときのm_staminaの割合
	float StaminaParcentage();

	// 生存フラグ無効化
	void EnableDead();

	// 自機1か2の入力情報を返す
	GameInput::INPUT_BUTTON GetStarInput(STAR_INPUT num);
	//-----------------------------------------------------

	// 自機を返す設定をする
	// CollisionObjectで使用
	Type GetObjectType()const override { 
		return PLAYER;
	}

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


	// テクスチャサイズ調整
	// 4*4サイズの統合画像で1枚を0.25倍ずつしたい時この値は{0.25f,0.25f}
	static const D3DXVECTOR2 TEXTURE_SIZE_OFFSET;

	// 画像分割
	// 4*4サイズの統合画像ならこの値は{4.f,4.f}
	static const D3DXVECTOR2 TEXTURE_PARTITION;

	// スタミナ最大値
	static const float MAX_STAMINA;

	// 敵との被弾時に減らされるスタミナ
	static const float DECREASE_STAMINA;

	// 敵と被弾後の無敵時間カウントの最大値
	// このフレーム数だけ無敵時間が行われる
	static const int MAX_INVISIBLE_COUNT;

	// 無敵時間による描画切り替えの切り替える時間
	// 描画切り替えを何フレーム区切りで行うか
	static const int INVISIBLE_DRAW_SWITCH_TIME;

private:
	// 被弾したときに無敵タイマーがカウントされる
	// この関数の内部で下記のInvisibleDrawSwitchが回っています
	void InvisibleCount();

	// 無敵時間と死亡による描画のONOFF
	// 無敵時間に入ると描画が一定の速度で点滅しますが死亡すると永続的に描画します
	void InvisibleDrawSwitch();

	// 自機との当たり判定後の処理
	// 基本的にEnemyとの当たりで使用する
	// 引数(当たりたいオブジェクトの種類)
	void HitAction(Type type)override;

private:
	std::string texture_list[MAX_TEXTURE_NUM];						// テクスチャ文字列保持
	std::string m_player_texture;									// 画像格納用
	GameInput::INPUT_BUTTON command_list[STAR_KEY_MAX];				// 自機それぞれのコマンドリスト
	D3DXVECTOR2 m_move;				// X、Y方向移動量
	float m_speed;					// 泳ぐときの速度
	float m_angle;					// 自機画像角度（MAX_ANGLEから-MAX_ANGLE度まで）
	float m_stamina;				// スタミナ（最大値はMAX_STAMINA）
	int m_state_change_timer;		// 状態遷移用タイマー		
	int m_invisible_count;			// 敵と被弾後の無敵時間カウント（最大値はMAX_INVISIBLE_COUNT）				
	bool m_draw_enable;				// 被弾時点滅用描画切り替え			
	bool m_swim_enable;				// 泳いでるフラグ(泳ぎ状態のときtrue)
	
	PlayerStateBase* m_p_state;					// ステート基底クラス			
	GameInput* m_p_game_input;					// 操作入力クラス
	IDirectSoundBuffer8* m_p_hit_se;			// 被弾SE
	Audio& m_p_audio = Audio::getInterface();	// オーディオインターフェース
};
