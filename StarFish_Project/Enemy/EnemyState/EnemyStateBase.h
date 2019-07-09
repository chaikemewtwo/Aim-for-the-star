#pragma once


class EnemyBase;

// 状態基底クラス
class StateBase {
public:
	virtual void Action(EnemyBase* e) = 0;

	virtual ~StateBase() {}
};
