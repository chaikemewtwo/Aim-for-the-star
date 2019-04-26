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
}


// 更新
void PlayerWaitState::Update(PlayerBase* p) {
	// 状態遷移タイマーインクリメント
	p->AddStateChangeTimer();

	// 待機状態が1回終わるごとに状態遷移タイマーリセット
	if(p->GetStateChangeTimer() <= MAX_COUNT){
		p->ResetStateChangeTimer();
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
