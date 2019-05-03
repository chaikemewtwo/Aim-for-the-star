#include "PlayerSwimState.h"
#include "../../PlayerBase/PlayerBase.h"


// 泳ぎ状態
// 初期化
void PlayerSwimState::Init(PlayerBase* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション1枚分タイマー
	m_animation_timer = 0;

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture("Resource/de_swim.png");
}


// 更新
void PlayerSwimState::Update(PlayerBase* p) {
	Keybord& kb = Keybord::getInterface();

	// 状態遷移タイマーインクリメント
	p->AddStateChangeTimer();
	p->SwimUp();

	// 重力付与
	p->AddGravity();

	// 左右角度変更
	// 左
	if ((kb.on('A'))) {
		p->AngleAdjust(false);
	}
	// 右
	if ((kb.on('D'))) {
		p->AngleAdjust(true);
	}

	// アニメーション1枚分タイマーインクリメント
	++m_animation_timer;
	if (m_animation_timer >= ONE_ANIMATION_SPEED) {
		p->AddAnimationNumber();
		m_animation_timer = 0;
	}

	// 待機状態が1回終わるごとに状態遷移タイマーリセット
	if (p->GetStateChangeTimer() >= MAX_COUNT) {
		p->ChangeState(PlayerWaitState::GetInstance());
	}
}
