#pragma once
#include "../PlayerBase/PlayerBase.h"


//-----------------------------------------------------
enum STATE {
	WAIT,				// 待機
	SWIM,				// 泳ぐ
	STANDING_WAIT,		// 立ち待機
	DAMAGE,				// ダメージ
	DEATH,				// 死亡状態
	MAX_STATE_NUMBER	// 最大値
};
//-----------------------------------------------------

// 状態基底クラス
class PlayerStateBase {
public:
	virtual void Init(PlayerBase * p) = 0;
	virtual void Update(PlayerBase * p) = 0;
	virtual ~PlayerStateBase() {};
protected:
};
