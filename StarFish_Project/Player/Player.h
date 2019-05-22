#pragma once

#include "../Lib/D3D/D3D9.h"
#include "../Lib/Window/Window.h"
#include "../Lib/Texture/Texture.h"
#include "../Lib/Texture/TextureBoad2D.h"
#include "../Lib/Input/KeyBord.h"
#include "../Lib/Input/GamePad.h"
#include "../CollisionObject/CircleCollisionObject.h"
#include "PlayerState\PlayerStateBase.h"

class MapChip;

// HACK:m_moveをm_vectorに変更した方がわかりやすい、それに伴いGetMovePos等も変更

class Player : public CircleCollisionObject {
public:	
	enum ID {
		STAR_1,
		STAR_2
	};

	enum IMPUT_KEY {
		LEFT_KEY,		// 左キー
		RIGHT_KEY,		// 右キー
		SWIM_KEY,		// 泳ぐキー
		PULL_ROPE_KEY,	// ロープ引っ張りキー

		MAX_KEY_NUM		// 最大値
	};

	// 入力キー文字列保持（操作分割のため）
	char imput_button_name[MAX_KEY_NUM][256];

	enum PLAYER_TEXTURE {
		WAIT_TEXTURE,
		STANDING_WAIT_TEXTURE,
		SWIM_TEXTURE,
		GRAB_TEXTURE,
		PULL_ROPE_TEXTURE,
		DEATH_TEXTURE,

		MAX_TEXTURE_NUM
	};

	bool swim_enable;

	// テクスチャ文字列保持
	// HACK:[256]を直す
	std::string star_texture_name[MAX_TEXTURE_NUM][256];

	// コンストラクタ（引数はプレイヤーのID）
	Player(ID id,MapChip *map_chip);
	// デストラクタ（まだ触れていない、ゲームメインの2周目に不具合が出る可能性あり）
	~Player() {}

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;

	//-----------------------------------------------------
	// 当たり判定で使用する関数
	// プレイヤー移動量ゲッター
	D3DXVECTOR2 GetMovePos() {
		return m_move;
	}

	// プレイヤー座標セッター
	void SetPos(D3DXVECTOR2 pos) {
		m_pos = pos;
	}

	void DecMoveY() {
		m_move.y += GRAVITY;
	}

	// プレイヤー移動量セッター
	void SetMovePos(D3DXVECTOR2 move) {
		m_move = move;
	}

	// ヒモ用（仮）
	void AddMove(D3DXVECTOR2 move) {
		m_move += move;
	}

	// 生存フラグゲッター
	bool GetIsAlive() {
		return is_alive;
	}
	//-----------------------------------------------------

	//-----------------------------------------------------
	// 状態遷移（各State）で使用する関数
	// 状態切り替え
	void ChangeState(PlayerStateBase* state) {
		m_state = state;
		m_state->Init(this);
	}

	// アニメーション番号0初期化
	void ResetAnimationNumber() {
		m_animation_num = 0;
	}

	// 重力負荷
	void AddGravity();

	// X方向向き変更
	void AngleAdjust(bool is_move_right);

	// 泳ぐ（ジャンプ）、傾いてる向きに移動
	void SwimUp();

	// 状態画像セッター
	void SetPlayerTexture(std::string new_player_texture) {
		m_player_texture = new_player_texture;
	}

	// 状態遷移タイマーゲッター
	int GetStateChangeTimer() {
		return m_state_change_timer;
	}

	// 状態遷移タイマー0初期化
	void ResetStateChangeTimer() {
		m_state_change_timer = 0;
	}

	// 状態遷移タイマーインクリメント
	void AddStateChangeTimer(){
		++m_state_change_timer;
	}

	// スタミナ最大値
	const int MAX_STAMINA = 1000;

	// スタミナゲッター
	int GetStamina() {
		return m_stamina;
	}

	// スタミナ減算
	void DecStamina(int dec_sutamina_num) {
		m_stamina -= dec_sutamina_num;
	}	

	// is_aliveをfalseに変更
	void DisableIsAlive() {
		is_alive = false;
	}
	//-----------------------------------------------------


	// MEMO:CollisionObjectで必要なので追加
	// 自機を返す設定をする
	Type GetObjectType()const override { 
		return PLAYER;
	}

	// 自機と敵との当たり判定後の処理(点滅させる)
	void HitAction(Type type)override;
		

private:
	// 無敵時間タイマー
	void GetDamageTimer();

	//-----------------------------------------------------
	// ゲーム内パラメータ用定数
	// 1フレームごとの画面下への移動量、重力負荷に使用
	const float GRAVITY = -1.f;

	// 向き変更時に1フレームごとに傾く角度
	const float ANGLE_ADD = 0.5f;

	// 向き変更時最大角度（ヒトデの頭の向きの左右の最大角度）
	const float MAX_ANGLE = 45.f;

	// STAR_1の初期位置
	const float STAR_1_FIRST_POS_X = (float)WINDOW_W / 2.f - 200.f;
	const float STAR_1_FIRST_POS_Y = (float)WINDOW_H / 2.f + 200.f;

	// STAR_2の初期位置
	const float STAR_2_FIRST_POS_X = (float)WINDOW_W / 2.f + 200.f;
	const float STAR_2_FIRST_POS_Y = (float)WINDOW_H / 2.f + 200.f;
	//-----------------------------------------------------

	//-----------------------------------------------------
	// 描画調整用定数
	// キャラのサイズは128×128ピクセル
	// テクスチャサイズ調整X座標用
	const float TEXTURE_SIZE_X = 0.25f;

	// テクスチャサイズ調整Y座標用
	const float TEXTURE_SIZE_Y = TEXTURE_SIZE_X;

	// 分割画像X枚数
	const int TEXTURE_PARTITION_X_NUMBER = 4;

	// 分割画像Y枚数
	const int TEXTURE_PARTITION_Y_NUMBER = TEXTURE_PARTITION_X_NUMBER;
	//-----------------------------------------------------

	// 変数 ------------------------------------------------
	// 画像格納用
	std::string m_player_texture;

	// X、Y方向移動量
	D3DXVECTOR2 m_move;

	// 自機画像角度（MAX_ANGLEから-MAX_ANGLE度まで）
	float m_character_angle;
	//-----------------------------------------------------

	// 状態遷移用タイマー
	int m_state_change_timer;

	// ステート基底クラスのインスタンス
	PlayerStateBase * m_state;

	// スタミナ
	int m_stamina;

	// 生存フラグ（DeathStateで当たり判定を取らないようにするため）
	bool is_alive;

	// 被弾時点滅用描画切り替え
	bool m_draw_enable;

	// 無敵時間
	int invisible_count;

	MapManager* m_map_manager;
};
