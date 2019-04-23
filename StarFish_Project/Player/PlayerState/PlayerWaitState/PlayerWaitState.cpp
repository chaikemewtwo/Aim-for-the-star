#include "PlayerWaitState.h"


// 待機状態（オブジェクト上以外、オブジェクト上での待機状態はStandingWaitState）
// 初期化
void PlayerWaitState::Init(PlayerBase* p) {
	// アニメーション番号
	p->SetAnimationNumber(0);
	// 
	p->SetTextureType(p->WAIT_TEXTURE);
}


// 更新
void PlayerWaitState::Update(PlayerBase* p) {
	// アニメーション番号更新（アニメーションの速さは考慮していない、高速で動く）
	for (int animation_num = 0; animation_num < MAX_TEXTURE_NUM; ++animation_num) {
		p->SetAnimationNumber(animation_num);
	}
}
