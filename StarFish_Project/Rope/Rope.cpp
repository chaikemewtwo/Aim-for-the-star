#include "Rope.h"
#include <cmath>


Rope::Rope(Player* p_1,Player* p_2) {
	m_p1 = p_1;
	m_p2 = p_2;
	
	m_sort_object = ROPE;
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
void Rope::PlayersDistanceAdjust() {
	if (MAX_ROPE_LEGTH < PlayersLadiusCalc()) {
		if (m_p1->GetMovePos() >= D3DXVECTOR2(0.f, 0.f)) {
			m_p2->SetMovePos(m_p2->GetMovePos() + m_p1->GetMovePos());
		}

		if (m_p2->GetMovePos() >= D3DXVECTOR2(1.f, 1.f)) {
			m_p1->SetMovePos(m_p1->GetMovePos() + m_p2->GetMovePos());
		}
	}

	////縄と距離の差分を算出
	//float dis =PlayersLadiusCalc()- MAX_ROPE_LEGTH;
	//auto distance = std::fabs(dis);
	//D3DXVECTOR2 new_pos = { 0,0 };
	//if (m_p1->GetPos().y < m_p2->GetPos().y) {
	//	new_pos.x = m_p1->GetPos().x - distance;
	//	new_pos.y = m_p1->GetPos().y - distance;
	//	m_p1->SetPos(new_pos);
	//}
	//else {
	//	new_pos.x = m_p2->GetPos().x - distance;
	//	new_pos.y = m_p2->GetPos().y - distance;
	//	m_p2->SetPos(new_pos);
	//}
}
