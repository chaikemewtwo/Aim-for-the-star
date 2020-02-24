#include"PlayerStandingWaitState.h"
#include"../PlayerDeathState/PlayerDeathState.h"
#include"../../../Player/Player.h"


const int PlayerStandingWaitState::ONE_ANIMATION_SPEED = 7;
const int PlayerStandingWaitState::MAX_ANIMATION_TEX_NUM = 7;


void PlayerStandingWaitState::Init(Player* p) {
	// AnimationDraw内でやっているので不必要の可能性あり
	//p->ResetAnimationCount();

	p->SetPlayerTexture(p->STANDING_WAIT_TEXTURE);
}


void PlayerStandingWaitState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();
	
	p->AnimationCount(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	// 泳ぎ状態へ移行
	if (kb.press(VK_SPACE)) {
		p->ChangeState(PlayerStandingWaitState::GetInstance());
	}
	// 死亡状態へ移行
	if (p->IsActive() == false) {
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
