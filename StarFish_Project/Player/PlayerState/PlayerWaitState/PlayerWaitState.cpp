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

	p->AnimationCount(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	p->AddGravity();

	// 左右角度変更
	// 左
	if (m_p_game_input->InputCommand(p->GetStarInput(p->KEY_LEFT), m_p_game_input->PUSH_ON)==true) {
		p->AngleAdjust(false);
	}
	// 右
	if (m_p_game_input->InputCommand(p->GetStarInput(p->KEY_RIGHT), m_p_game_input->PUSH_ON) == true) {
		p->AngleAdjust(true);
	}

	// 泳ぎ状態へ移行
	if (m_p_game_input->InputCommand(p->GetStarInput(p->KEY_SWIM), m_p_game_input->PUSH_ENTER) == true) {
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
