#include "PlayerWaitState.h"
#include "../PlayerSwimState/PlayerSwimState.h"
#include "../../PlayerBase/PlayerBase.h"

// 待機状態（オブジェクト上以外、オブジェクト上での待機状態はStandingWaitState）
// 初期化
void PlayerWaitState::Init(PlayerBase* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション1枚分タイマー
	m_animation_timer = 0;

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture("Resource/de_wait.png");
}


// 更新
void PlayerWaitState::Update(PlayerBase* p) {
	Keybord& kb = Keybord::getInterface();
	// 状態遷移タイマーインクリメント
	p->AddStateChangeTimer();

	// 待機状態が1回終わるごとに状態遷移タイマーリセット
	if(p->GetStateChangeTimer() <= MAX_COUNT){
		p->ResetStateChangeTimer();
	}

	// 泳ぎ状態へ移行
	if (kb.press(VK_SPACE)) {
		p->ChangeState(PlayerSwimState::GetInstance());
	}

	// アニメーション1枚分タイマーインクリメント
	++m_animation_timer;
	if (m_animation_timer >= ONE_ANIMATION_SPEED) {
		p->AddAnimationNumber();
		m_animation_timer = 0;
		if (p->GetAnimationNumber() >= MAX_TEXTURE_NUM) {
			p->ResetAnimationNumber();
		}
	}
}
