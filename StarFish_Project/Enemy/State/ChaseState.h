#pragma once
#include"StateBase.h"
#include"../Enemy/SeaUrchin.h"

// 追跡クラス
class Chase :public StateBase {
public:
	// シングルトン
	static Chase *GetInstance();
	void Action(EnemyBase* e)override;
private:
	~Chase() {}
};
