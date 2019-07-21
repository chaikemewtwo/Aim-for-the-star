#pragma once

#include"EnemyBase.h"


// ウニクラス
class SeaUrchin :public EnemyBase {
public:
	SeaUrchin(const D3DXVECTOR2 pos, Map* const map_chip, bool cam_move = true);
	~SeaUrchin()override {}	

	void Update()override;
	void Draw()override;
	/*
	ウニの遷移
	WaitState　　　　：m_can_moveがfalseの場合はWaitStateで固定
	VerticalMoveState：それ以外はVerticalMoveStateで固定
	*/
	StateId CheckChangeState()override;
};
