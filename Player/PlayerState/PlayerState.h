#pragma once
#include "../PlayerBase/PlayerBase.h"


// 状態基底クラス
class PlayerStateBase {
public:
	virtual void Update(PlayerBase* p) = 0;
	virtual void Draw(PlayerBase* p) = 0;
	~PlayerStateBase() {};
};


// 待機状態(落下)
class WaitState : PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;

};


// 泳ぎ状態
class SwimState : PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;
};


// オブジェクトなどの上に立つ
class StandOnState : PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;

};


// 被弾
class DamageState : PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;
};


// 死亡
class DeathState : PlayerStateBase {
public:
	void Update(PlayerBase* p) override;
	void Draw(PlayerBase* p) override;

};
