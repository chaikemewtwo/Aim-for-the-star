#pragma once

#include"EnemyBase.h"


// ウニクラス
class SeaUrchin :public EnemyBase {
public:
	// コンストラクタの引数に初期位置を入れる
	SeaUrchin(D3DXVECTOR2 pos, MapTip* map_tip, bool no_move = false);
	~SeaUrchin()override {}	

	void Init()override;
	void Update()override;
	void Draw()override;
	void ChangeState(StateBase* state)override;

private:
	// 状態を保存する変数
	StateBase* m_pstate_base;
};
