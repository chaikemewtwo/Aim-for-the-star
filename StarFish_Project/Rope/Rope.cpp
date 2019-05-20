#include "Rope.h"
#include <cmath>


Rope::Rope(Player* p_1, Player* p_2) {
	m_p1 = p_1;
	m_p2 = p_2;
}


void Rope::Update() {
	m_p1_pos = m_p1->GetPos();
	m_p2_pos = m_p2->GetPos();

	PlayersDistanceAdjust();
}


void Rope::Draw() {
	Texture::Draw2D(
		"Resource/Texture/Player/himo.png",
		m_p1_pos.x,
		m_p1_pos.y,
		0.5f / LengthAdjust(),
		0.5f,
		AngleCalc()
	);
}


float Rope::AngleCalc() {
	// 弧度法に変換
	float angle = atan2((m_p2_pos.y - m_p1_pos.y) ,
		(m_p2_pos.x - m_p1_pos.x)) * (180.f / 3.14f);
	return angle;
}


float Rope::PlayersLadiusCalc() {
	// 2点間の距離を算出
	float distance = (((m_p2_pos.x - m_p1_pos.x)* (m_p2_pos.x - m_p1_pos.x)) +
		((m_p2_pos.y - m_p1_pos.y)*(m_p2_pos.y - m_p1_pos.y)));
	// 2点間の距離から半径算出
	float radius = sqrt(distance);
	return radius;
}


float Rope::LengthAdjust() {
	// 長さの比率を返す
	return MAX_ROPE_LEGTH / PlayersLadiusCalc();
}


// テストコード
float Rope::PlayersDistanceAdjust() {
	if (MAX_ROPE_LEGTH <= PlayersLadiusCalc()) {
		if (m_p1->GetMovePos() >= (0,0)) {
			m_p2->AddMove(m_p1->GetMovePos());
		}
		if (m_p2->GetMovePos() >= (0, 0)) {
			m_p1->AddMove(m_p2->GetMovePos());
		}
	}
}
