#pragma once

#include "../Player/Player.h"

// ロープは650×16

class Rope:public Object {
public:
	Rope(Player* p1,Player* p2);

	void Update()override;
	void Draw()override;

private:
	Player* m_p1;
	Player* m_p2;

	// ロープの最大の長さ
	const float MAX_ROPE_LEGTH = 650;

	// 向き計算
	float AngleCalc();

	// プレイヤー2体から半径算出
	float PlayersLadiusCalc();

	// 長さ調節
	float LengthAdjust();

	// プレイヤー2体を一定以上離れなくする
	float PlayersDistanceAdjust();

	D3DXVECTOR2 m_p1_pos;
	D3DXVECTOR2 m_p2_pos;
};

