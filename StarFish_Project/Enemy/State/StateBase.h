#pragma once

//enum StateType {
//	Wait,			// 待機
//	Chase,			// 追跡
//	Side,			// 横移動
//	SideParabola,	// 横放物線移動
//	Vertical		// 縦移動
//};

class EnemyBase;

// 状態基底クラス
class StateBase {
public:
	virtual void Action(EnemyBase* e) = 0;
	virtual ~StateBase() {}
};
