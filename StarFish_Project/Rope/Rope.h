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
	const float MAX_ROPE_LEGTH = 650.f;

	// 向き計算
	float AngleCalc();

	// プレイヤー2体から半径算出
	float PlayersRadiusCalc();

	// 長さ調節
	float LengthPercentage();

	// プレイヤー2体を一定以上離れなくする
	void PlayersDistanceAdjust();
};
