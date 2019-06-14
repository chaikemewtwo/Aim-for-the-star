#pragma once
#include"../PlayerStateBase.h"
#include"../../../Lib/Sound/DirectSound.h"


// 泳ぎ状態
class PlayerSwimState : public PlayerStateBase {
public:
	static PlayerSwimState *GetInstance()
	{
		static PlayerSwimState instance;
		return &instance;
	}

	void Init(Player* p) override;
	void Update(Player* p) override;

private:
	// 1アニメーションの速さ
	// この速さで1アニメーションが進んでいく
	static const int ONE_ANIMATION_SPEED;

	// 統合画像内のアニメーション枚数
	// 1つの統合画像にキャラの画像が詰め込んであるか
	static const int MAX_ANIMATION_TEX_NUM;

	// 状態切り替えカウント
	// GetStateChangeTimer()がこのカウントを満たすと待機状態に戻る
	static const int CHANGE_STATE_COUNT;

	// 泳ぎ状態へ移行する際に使用するスタミナ
	// スタミナがこれ以下のときでも泳ぐことができるが死んでしまう
	static const int TO_SWIM_USE_STAMINA;

private:
	IDirectSoundBuffer8* m_p_swim_se;	// 泳ぐSE

	Audio& m_p_audio = Audio::getInterface();	// オーディオ
};
