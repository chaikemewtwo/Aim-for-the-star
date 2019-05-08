#include "PlayerSwimState.h"
#include "../../PlayerBase/PlayerBase.h"


// 泳ぎ状態
// 初期化
void PlayerSwimState::Init(PlayerBase* p) {
	// 状態遷移タイマー
	p->ResetStateChangeTimer();

	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture("Resource/de_swim.png");
}


// 更新
void PlayerSwimState::Update(PlayerBase* p) {
	Keybord& kb = Keybord::getInterface();

	// アニメーション
	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);

	// 状態遷移タイマーインクリメント
	p->AddStateChangeTimer();

	// 泳ぐ関数呼び出し
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

	// 待機状態が1回終わるごとに状態遷移タイマーリセット
	if (p->GetStateChangeTimer() >= MAX_COUNT) {
		p->ChangeState(PlayerWaitState::GetInstance());
	}
}
