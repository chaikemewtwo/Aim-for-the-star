#include "PlayerStandingWaitState.h"
#include "../../PlayerBase/PlayerBase.h"


// 立ち待機状態
// 初期化
void PlayerStandingWaitState::Init(PlayerBase* p) {
	// アニメーション番号
	p->ResetStateChangeTimer();
}


// 更新
void PlayerStandingWaitState::Update(PlayerBase* p) {
	// アニメーション番号更新（まだアニメーションの速さは考慮しておらず、高速で動く）
	for (int animation_num = 0; animation_num < MAX_TEXTURE_NUM; ++animation_num) {
		p->ResetAnimationNumber();
	}
}
