#include "PlayerSwimState.h"


// 泳ぎ状態
// 初期化
void PlayerSwimState::Init(PlayerBase* p) {
	count = 0;
	// アニメーション番号
	p->SetAnimationNumber(0);
	// 描画する画像の変更
	p->SetTextureType(p->SWIM_TEXTURE);
}


// 更新
void PlayerSwimState::Update(PlayerBase* p) {
	/*++count;
	if (count <= MAX_COUNT) {
		p->ChangeState(new WaitState);
	}*/
}
