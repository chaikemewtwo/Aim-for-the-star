#pragma once
#include"../PlayerStateBase.h"
#include"../../../Lib/Sound/DirectSound.h"
#include"../../../GameInput/GameInput.h"


// 泳ぎ状態
class PlayerSwimState : public PlayerStateBase {
public:
	// インスタンス取得
	static PlayerSwimState *GetInstance()
	{
		static PlayerSwimState instance;
		return &instance;
	}

	void Init(Player* p) override;
	void Update(Player* p) override;

private:
	// 1アニメーションの速さ
	// この速さで1アニメーションが進んでいきます
	static const int ONE_ANIMATION_SPEED;

	// 統合画像内のアニメーション枚数
	// 1つの統合画像にキャラの画像が詰め込んであるか
	static const int MAX_ANIMATION_TEX_NUM;

	// 状態切り替えカウント
	// GetStateChangeTimer()がこのカウントを満たすと待機状態に戻ります
	static const int CHANGE_STATE_COUNT;

	// 泳ぎ状態へ移行する際に使用するスタミナ
	// スタミナがこれ以下のときでも泳ぐことが可能ですがが死んでしまいます
	static const float TO_SWIM_USE_STAMINA;

private:
	IDirectSoundBuffer8* m_p_swim_se;			// 泳ぐSE

	Audio& m_p_audio = Audio::getInterface();	// オーディオ

	GameInput * m_p_game_input;					// 入力
};
