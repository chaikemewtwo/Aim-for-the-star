#include "PlayerDeathState.h"
#include "../../PlayerBase/PlayerBase.h"


// 死亡状態
// 初期化
void PlayerDeathState::Init(PlayerBase* p) {
	// アニメーション番号
	p->ResetAnimationNumber();

	// 状態画像変更
	p->SetPlayerTexture("Resource/de_wait.png");
}


// 更新
void PlayerDeathState::Update(PlayerBase* p) {
	// 重力付与
	p->AddGravity();

	// アニメーション
	p->AnimationDraw(MAX_ANIMATION_TEX_NUM, ONE_ANIMATION_SPEED);
}
