#pragma once
#include "../../Lib/D3D/D3D9.h"
#include "../../Lib/Window/Window.h"
#include "../../Lib/Texture/Texture.h"
#include "../../Lib/Texture/TextureBoad2D.h"
#include "../../Lib/Input/KeyBord.h"
#include "../../GameObject/Object/Object.h"
#include "../PlayerState/PlayerStateBase.h"

// MEMO:自機1と2の操作が同一になっています（分割する必要あり）

class PlayerBase : public Object {
public:	
	// コンストラクタ
	PlayerBase();
	// 仮想デストラクタ
	virtual ~PlayerBase() {}

	// ゲームシーンで使用する関数 -------------------------
	// 更新処理
	// HACK：自機2も自機1の操作方法になっているので操作の分離が必要
	void Update();

	// 描画処理
	// MEMO:自機2も自機1の画像を使用中、自機2の画像が完成次第変更する
	void Draw();
	//-----------------------------------------------------


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
	// アニメーション番号ゲッター
	int GetAnimationNumber() {
		return m_animation_number;
	}

	// アニメーション番号0初期化
	void ResetAnimationNumber() {
		m_animation_number = 0;
	}

	// アニメーション番号インクリメント
	int AddAnimationNumber() {
		m_animation_number++;
		return m_animation_number;
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
	int AddStateChangeTimer(){
		++m_state_change_timer;
		return m_state_change_timer;
	}
	//-----------------------------------------------------

protected:

	//-----------------------------------------------------
	// ゲーム内パラメータ用定数
	// 重力負荷
	const float GRAVITY = 1.f;

	// 角度変換
	const float ANGLE_ADD = 0.5f;

	// 向き変更時最大角度（ヒトデの頭の向きの左右の最大角度）
	const float MAX_ANGLE = 45.f;

	// 泳ぎインターバル
	const int SWIM_INTERVAL = 96;

	// 泳ぎアニメーション補助用
	// HACK:SwimStateに移行する
	const int SWIM_ANIMATION_SUPPORT_NUMBER = 6;
	//-----------------------------------------------------

	//-----------------------------------------------------
	// 描画調整用定数
	// テクスチャサイズ調整X座標用
	const float TEXTURE_SIZE_X = 0.25f;

	// テクスチャサイズ調整Y座標用
	const float TEXTURE_SIZE_Y = 0.25f;

	// 分割画像X枚数
	const int TEXTURE_PARTITION_X_NUMBER = 4;

	// 分割画像Y枚数
	const int TEXTURE_PARTITION_Y_NUMBER = 4;
	//-----------------------------------------------------

	// 関数 ------------------------------------------------
	// 重力負荷
	void AddGravity();

	// X方向向き変更
	void AngleAdjust(bool is_move_right);
	
	// 変数 ------------------------------------------------
	// 画像格納用
	// HACK:配列にenum突っ込んだ方がいいかも、自機が2種類分あるので工夫する必要がある
	std::string m_player_texture;

	// X、Y方向移動量
	D3DXVECTOR2 m_move;

	// 自機画像角度
	float m_character_angle;

	// アニメーション番号（統合画像のどの画像を描画するか）
	int m_animation_number;

	// ステート（状態）

	// 泳ぎクールタイム計測用
	// HACK:Stateパターン内で管理する
	int m_swim_interval_count;
	//-----------------------------------------------------

private:
	// 状態遷移用タイマー
	int m_state_change_timer;

	PlayerStateBase * m_state;

	// 関数　----------------------------------------------
	// 泳ぐ（ジャンプ）、傾いてる向きに移動
	// HACK:Stateに書き直す
	void SwimUp();
	//-----------------------------------------------------
};
