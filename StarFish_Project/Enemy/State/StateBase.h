#pragma once

//enum StateType {
//	Wait,			// 待機
//	Chase,			// 追跡
//	Side,			// 横移動
//	SideParabola,	// 横放物線移動
//	Vertical		// 縦移動
//};

// 状態基底クラス
class StateBase {
public:
	virtual void Action() = 0;
	virtual ~StateBase() {}
protected:
};
