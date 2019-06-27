#include "PlayerDeathState.h"
#include "../../Player/Player.h"


const int PlayerDeathState::ONE_ANIMATION_SPEED = 10;
const int PlayerDeathState::MAX_ANIMATION_TEX_NUM = 16;
const int PlayerDeathState::ANIMATION_INIT_COUNT = 11;


// 死亡状態
// 初期化
void PlayerDeathState::Init(Player* p) {
	// AnimationDraw内でやっているので不必要の可能性あり
	//p->ResetAnimationCount();

	p->SetPlayerTexture(p->DEATH_TEXTURE);
}


// 更新
void PlayerDeathState::Update(Player* p) {
	p->AddGravity();

	p->AnimationCount(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED, ANIMATION_INIT_COUNT);
}
