#include"PlayerStandingWaitState.h"
#include"../PlayerDeathState/PlayerDeathState.h"
#include"../../Player/Player.h"


// 1アニメーションの速さ
const int PlayerStandingWaitState::ONE_ANIMATION_SPEED = 7;
// 統合画像内の画像枚数
const int PlayerStandingWaitState::MAX_ANIMATION_TEX_NUM = 7;


// 立ち待機状態
// 初期化
void PlayerStandingWaitState::Init(Player* p) {
	p->ResetAnimationCount();

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
	// 死亡状態へ移行
	if (p->IsActive() == false) {
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
