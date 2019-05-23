#include "PlayerWaitState.h"
#include "../PlayerSwimState/PlayerSwimState.h"
#include "../PlayerDeathState/PlayerDeathState.h"
#include "../../Player/Player.h"


// 待機状態（オブジェクト上以外、オブジェクト上での待機状態はStandingWaitStateクラス）
// 初期化
void PlayerWaitState::Init(Player* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture(p->star_texture_name[p->WAIT_TEXTURE]);
}


// 更新
void PlayerWaitState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();

	p->swim_enable = false;

	// アニメーション
	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	// 重力付与
	p->AddGravity();

	// 左右角度変更
	// 左
	if ((kb.on(p->imput_button_name[p->LEFT_KEY][256]))) {
		p->AngleAdjust(false);
	}
	// 右
	if ((kb.on(p->imput_button_name[p->RIGHT_KEY][256]))) {
		p->AngleAdjust(true);
	}

	if (p->GetStamina() >= TO_SWIM_NEEDED_STAMINA && kb.press(p->imput_button_name[p->SWIM_KEY][256])) {
		// スタミナ減算
		p->DecStamina(TO_SWIM_NEEDED_STAMINA);

		// 泳ぎ状態へ移行
		p->ChangeState(PlayerSwimState::GetInstance());		
	}

	if (p->GetIsAlive() == false) {
		// 死亡状態へ移行
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
