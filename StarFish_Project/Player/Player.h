#pragma once

#include "../Lib/D3D/D3D9.h"
#include "../Lib/Window/Window.h"
#include "../Lib/Texture/Texture.h"
#include "../Lib/Texture/TextureBoad2D.h"
#include "../Lib/Input/KeyBord.h"
#include "../Lib/Input/GamePad.h"
#include "../CollisionObject/CircleCollisionObject.h"
#include "PlayerState\PlayerStateBase.h"

// MEMO:自機1と2の操作が同一になっています（分割する必要あり）

class Player : public CircleCollisionObject {
public:	
	enum PLAYER_ID {
		STAR_1,
		STAR_2
	};

	enum PLAYER_IMPUT_BUTTON {
		LEFT_ANGLE_ADJUST_KEY,
		RIGHT_ANGLE_ADJUST_KEY,
		SWIM_KEY,
		GRAB_KEY,
		PULL_ROPE_KEY
	};


	// コンストラクタ
	Player(PLAYER_ID id);
	// 仮想デストラクタ
	virtual ~Player() {}

	// 更新処理
	// HACK：自機2も自機1の操作方法になっているので操作の分離が必要
	void Update()override;

	// 描画処理
	// MEMO:自機2も自機1の画像を使用中、自機2の画像が完成次第変更する
	void Draw()override;

	// 当たり判定で使用する関数	---------------------------
	// プレイヤー座標ゲッター
	D3DXVECTOR2 GetPos() {
		return m_pos;
	}

	// プレイヤー移動量ゲッター
	D3DXVECTOR2 GetMovePos() {
		return m_move;
	}

	// プレイヤー座標セッター
	void SetPos(D3DXVECTOR2 pos) {
		m_pos = pos;
	}

	// プレイヤー移動量セッター
	void SetMovePos(D3DXVECTOR2 move) {
		m_move = move;
	}
	//-----------------------------------------------------


	// 状態遷移（各State）で使用する関数 ------------------
	// 状態切り替え
	void ChangeState(PlayerStateBase* state) {
		m_state = state;
		m_state->Init(this);
	}

	// アニメーション番号0初期化
	void ResetAnimationNumber() {
		m_animation_num = 0;
	}

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

	// スタミナゲッター
	int GetStamina() {
		return m_stamina;
	}

	// スタミナセッター
	void DecStamina(int dec_sutamina_num) {
		m_stamina -= dec_sutamina_num;
	}

	// 泳ぐ（ジャンプ）、傾いてる向きに移動
	void SwimUp();

	// 重力負荷
	void AddGravity();

	// X方向向き変更
	void AngleAdjust(bool is_move_right);
	//-----------------------------------------------------


	// MEMO:CollisionObjectで必要なので追加
	// 自機を返す設定をする
	Type GetObjectType()const override { 
		return PLAYER;
	}

	// 自機と敵との当たり判定後の処理(点滅させる)
	void HitAction(Type type)override;
	
protected:

	//-----------------------------------------------------
	// ゲーム内パラメータ用定数
	// 1フレームごとの画面下への移動量、重力負荷に使用
	const float GRAVITY = -1.f;

	// 向き変更時に1フレームごとに傾く角度
	const float ANGLE_ADD = 0.5f;

	// 向き変更時最大角度（ヒトデの頭の向きの左右の最大角度）
	const float MAX_ANGLE = 45.f;
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
	// HACK:自機が2種類分あるので工夫する必要がある
	std::string m_player_texture;

	// X、Y方向移動量
	D3DXVECTOR2 m_move;

	// 自機画像角度（MAX_ANGLEから-MAX_ANGLE度まで）
	float m_character_angle;
	//-----------------------------------------------------

private:
	// 状態遷移用タイマー
	int m_state_change_timer;

	// ステート基底クラスのインスタンス
	PlayerStateBase * m_state;

	// スタミナ
	int m_stamina;

	// スタミナ最大値
	const int MAX_SUTAMINA = 1000;

	// 被弾時点滅用描画切り替え
	bool m_draw_enable;
};
