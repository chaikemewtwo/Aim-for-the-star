#include "PlayerDamageState.h"


// 被弾状態
// 初期化
void PlayerDamageState::Init(PlayerBase* p) {
	count = 0;
	// アニメーション番号
	p->SetAnimationNumber(0);
	// 状態に適した画像に変更
	p->SetTextureType(SWIM);
}


// 更新
void PlayerDamageState::Update(PlayerBase* p) {
	// アニメーション番号更新（まだアニメーションの速さは考慮しておらず、高速で動く）
	for (int animation_num = 0; animation_num < MAX_TEXTURE_NUM; ++animation_num) {
		p->SetAnimationNumber(animation_num);
	}
}
