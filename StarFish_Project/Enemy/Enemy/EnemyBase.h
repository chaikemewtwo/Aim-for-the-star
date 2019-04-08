#pragma once
#include"../State/StateBase.h"
#include"../State/ChaseState.h"
#include"../State/SideMoveState.h"
#include"../State/VerticalMoveState.h"
#include"../State/WaitState.h"

// 敵基底クラス
class EnemyBase {
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	//virtual void ChangeState() = 0;
	virtual void Draw() = 0;
protected:
	// 現在の状態変数
	StateBase *pm_state_base;
private:
};
