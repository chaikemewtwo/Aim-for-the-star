#include "PlayerStandingWaitState.h"
#include "../../Player/Player.h"


// 立ち待機状態
// 初期化
void PlayerStandingWaitState::Init(Player* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture(p->star_texture_name[p->STANDING_WAIT_TEXTURE]);
}


// 更新
void PlayerStandingWaitState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();

	// アニメーション
	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	// 泳ぎ状態へ移行
	if (kb.press(VK_SPACE)) {
		p->ChangeState(PlayerStandingWaitState::GetInstance());
	}
}
