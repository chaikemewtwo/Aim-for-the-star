#include "PlayerWaitState.h"
#include "../PlayerSwimState/PlayerSwimState.h"
#include "../PlayerDeathState/PlayerDeathState.h"
#include "../../Player/Player.h"
#include "../../../Lib/Sound/DirectSound.h"


const int PlayerWaitState::ONE_ANIMATION_SPEED = 10;
const int PlayerWaitState::MAX_ANIMATION_TEX_NUM = 6;


void PlayerWaitState::Init(Player* p) {
	p->ResetAnimationCount();

	p->SetPlayerTexture(p->star_texture_name[p->WAIT_TEXTURE]);

	p->swim_enable = false;
}


void PlayerWaitState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();	

	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	p->AddGravity();

	// 左右角度変更
	// PlayerのMAX_ANGLEまで傾けることができる
	// 左
	if ((kb.on(p->imput_button_name[p->LEFT_KEY]))) {
		p->AngleAdjust(false);
	}
	// 右
	if ((kb.on(p->imput_button_name[p->RIGHT_KEY]))) {
		p->AngleAdjust(true);
	}

	if (kb.press(p->imput_button_name[p->SWIM_KEY])) {
		// 泳ぎ状態へ移行
		p->ChangeState(PlayerSwimState::GetInstance());		
	}

	if (p->IsActive() == false) {
		// 死亡状態へ移行
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
