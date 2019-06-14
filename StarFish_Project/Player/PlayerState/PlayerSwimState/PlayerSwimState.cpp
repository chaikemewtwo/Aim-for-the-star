#include"PlayerSwimState.h"
#include"../PlayerWaitState/PlayerWaitState.h"
#include"../PlayerDeathState/PlayerDeathState.h"
#include"../../Player/Player.h"


const int PlayerSwimState::ONE_ANIMATION_SPEED = 6;
const int PlayerSwimState::MAX_ANIMATION_TEX_NUM = 16;
const int PlayerSwimState::CHANGE_STATE_COUNT = ONE_ANIMATION_SPEED * MAX_ANIMATION_TEX_NUM;
const int PlayerSwimState::TO_SWIM_USE_STAMINA = 200;


void PlayerSwimState::Init(Player* p) {
	p->ResetStateChangeTimer();

	p->ResetAnimationCount();

	p->SetPlayerTexture(p->star_texture_name[p->SWIM_TEXTURE]);

	p->swim_enable = true;

	p->DecStamina(TO_SWIM_USE_STAMINA);

	m_p_swim_se = m_p_audio.getCloneBuffer("Resource/Sound/Player/swim1.wav");

	m_p_swim_se->Play(0,0,0);
}


void PlayerSwimState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();

	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	p->AddStateChangeTimer();

	p->SwimUp();

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

	// 待機状態に戻る
	if (p->GetStateChangeTimer() >= CHANGE_STATE_COUNT) {
		p->ChangeState(PlayerWaitState::GetInstance());
	}

	// 死亡状態へ移行
	if (p->IsActive() == false) {
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
