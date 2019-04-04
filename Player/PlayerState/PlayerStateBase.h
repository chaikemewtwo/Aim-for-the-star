#pragma once
#include "../PlayerBase/PlayerBase.h"


// 状態基底クラス
class PlayerStateBase {
public:
	virtual void Update(PlayerBase* p) = 0;
	virtual void Draw(PlayerBase* p) = 0;
	~PlayerStateBase() {};
};
