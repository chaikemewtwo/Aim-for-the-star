#pragma once
#include"EnemyBase.h"

// ウニクラス
class SeaUrchin :public EnemyBase {
public:
	SeaUrchin(float x, float y);
	~SeaUrchin()override {}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ChangeState(StateBase* state)override;

private:
	// 状態を保存する変数
	StateBase* m_pstate_base;
};
