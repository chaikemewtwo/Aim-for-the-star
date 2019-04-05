#pragma once
#include"StateBaseh.h"

// 敵基底クラス
class EnemyBase {
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void ChangeState() = 0;
protected:
	// 現在の状態変数
	StateBase *m_pstate_base;
private:
};
