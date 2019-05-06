#include "PlayerStandingWaitState.h"
#include "../../PlayerBase/PlayerBase.h"


// 立ち待機状態
// 初期化
void PlayerStandingWaitState::Init(PlayerBase* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション1枚分タイマー
	m_animation_timer = 0;

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture("Resource/de_standing_wait.png");
}


// 更新
void PlayerStandingWaitState::Update(PlayerBase* p) {
	Keybord& kb = Keybord::getInterface();

	// 泳ぎ状態へ移行
	if (kb.press(VK_SPACE)) {
		p->ChangeState(PlayerStandingWaitState::GetInstance());
	}

	// アニメーション1枚分タイマーインクリメント
	++m_animation_timer;

	// アニメーションタイマーが1回のアニメーション分の長さ以上になったら
	if (m_animation_timer >= ONE_ANIMATION_SPEED) {
		// アニメーション番号インクリメント
		p->AddAnimationNumber();

		// アニメーションタイマーをリセット
		m_animation_timer = 0;

		// アニメーション番号が統合画像内の枚数以上になったら
		if (p->GetAnimationNumber() >= MAX_TEXTURE_NUM) {
			// アニメーション番号をリセット
			p->ResetAnimationNumber();
		}
	}
}
