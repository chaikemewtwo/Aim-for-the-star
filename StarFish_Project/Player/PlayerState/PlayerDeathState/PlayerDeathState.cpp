#include "PlayerDeathState.h"
#include "../../PlayerBase/PlayerBase.h"


// 死亡状態
// 初期化
void PlayerDeathState::Init(PlayerBase* p) {
	// アニメーション番号
	p->ResetAnimationNumber();
}


// 更新
void PlayerDeathState::Update(PlayerBase* p) {
	// アニメーション番号更新（まだアニメーションの速さは考慮しておらず、高速で動く）
	for (int animation_num = 0; animation_num < MAX_TEXTURE_NUM; ++animation_num) {
		p->ResetAnimationNumber();
	}
}
