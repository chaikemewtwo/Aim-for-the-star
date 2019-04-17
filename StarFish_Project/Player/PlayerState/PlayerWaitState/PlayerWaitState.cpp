#include "PlayerWaitState.h"


// 待機状態（オブジェクト上以外、オブジェクト上での待機状態はStandingWaitState）
// 初期化
void PlayerWaitState::Init(PlayerBase* p) {
	// アニメーション番号
	p->SetAnimationNumber(0);
	p->WAIT;
}


// 更新
void PlayerWaitState::Update(PlayerBase* p) {
	Keybord& kb = Keybord::getInterface();

	// テスト用なので自機1の操作を使用
	// 泳ぎ状態へ移行
	//if (kb.press('V')) {
	//	p->ChangeState(new SwimState);
	//}
}
