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
		0.5f,
		0.5f,
		AngleCalc()
	);
}


// HACK:自機1と2のX座標の大きさが入れ替わるとリセットされる（-の値が入らない）
float Rope::AngleCalc() {
	float angle = atan((m_p2_pos.y - m_p1_pos.y) / (m_p2_pos.x - m_p1_pos.x)) * (180.f / 3.14f);
	return angle;
}


//float Rope::LengthAdjust(float pos_A, float pos_B) {
//	pos_A
//}
