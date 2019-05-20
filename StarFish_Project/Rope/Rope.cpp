#include "Rope.h"
#include <cmath>


Rope::Rope(Player* p_1, Player* p_2) {
	m_p1 = p_1;
	m_p2 = p_2;
}


void Rope::Update() {
	m_p1_pos = m_p1->GetPos();
	m_p2_pos = m_p2->GetPos();
		
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
	float angle = atan2((m_p2_pos.y - m_p1_pos.y) , (m_p2_pos.x - m_p1_pos.x)) * (180.f / 3.14f);
	return angle;
}


float Rope::LengthAdjust() {
	// 2点間の距離を算出
	float distance = (((m_p2_pos.x - m_p1_pos.x)* (m_p2_pos.x - m_p1_pos.x)) + ((m_p2_pos.y - m_p1_pos.y)*(m_p2_pos.y - m_p1_pos.y)));
	float percentage = sqrt(distance);
	// 長さの比率を返す
	return MAX_ROPE_LEGTH / percentage;
}
