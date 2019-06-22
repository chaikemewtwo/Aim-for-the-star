#include"PlayerWaitState.h"
#include"../PlayerSwimState/PlayerSwimState.h"
#include"../PlayerStandingWaitState/PlayerStandingWaitState.h"
#include"../PlayerDeathState/PlayerDeathState.h"
#include"../../Player/Player.h"
#include"../../../Lib/Sound/DirectSound.h"


const int PlayerWaitState::ONE_ANIMATION_SPEED = 10;
const int PlayerWaitState::MAX_ANIMATION_TEX_NUM = 6;


void PlayerWaitState::Init(Player* p) {
	p->ResetAnimationCount();

	p->SetPlayerTexture(p->WAIT_TEXTURE);

	p->SetSwimEnable(false);
}


void PlayerWaitState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();	

	// HACK:各StateのAnimationDrawはplayerのDrawでやったほうがいいかも　19/06/17
	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	p->AddGravity();

	// 左右角度変更
	// 左
	if ((kb.on(p->imput_button_list[p->LEFT_KEY]))) {
		p->AngleAdjust(false);
	}
	// 右
	if ((kb.on(p->imput_button_list[p->RIGHT_KEY]))) {
		p->AngleAdjust(true);
	}

	if (kb.press(p->imput_button_list[p->SWIM_KEY])) {
		// 泳ぎ状態へ移行
		p->ChangeState(PlayerSwimState::GetInstance());		
	}

	// 未実装、岩オブジェクトとの当たり判定がとれ次第実装します
	//if (p->) {
	//	// 立ち待機状態へ移行
	//	p->ChangeState(PlayerStandingWaitState::GetInstance());
	//}

	if (p->IsActive() == false) {
		// 死亡状態へ移行
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
