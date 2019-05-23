#include "PlayerSwimState.h"
#include "../PlayerDeathState/PlayerDeathState.h"
#include "../../Player/Player.h"


// 泳ぎ状態
// 初期化
void PlayerSwimState::Init(Player* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture(p->star_texture_name[p->SWIM_TEXTURE]);
}


// 更新
void PlayerSwimState::Update(Player* p) {
	Keybord& kb = Keybord::getInterface();

	// アニメーション
	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	// 状態遷移タイマーインクリメント
	p->AddStateChangeTimer();

	// 泳ぐ関数呼び出し
	p->SwimUp();

	// 左右角度変更
	// 左
	if ((kb.on(p->imput_button_name[p->LEFT_KEY][256]))) {
		p->AngleAdjust(false);
	}
	// 右
	if ((kb.on(p->imput_button_name[p->RIGHT_KEY][256]))) {
		p->AngleAdjust(true);
	}

	if (p->GetStateChangeTimer() >= MAX_COUNT) {
		p->ChangeState(PlayerWaitState::GetInstance());
	}

	if (p->GetIsAlive() == false) {
		// 死亡状態へ移行
		p->ChangeState(PlayerDeathState::GetInstance());
	}
}
