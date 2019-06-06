#include "Rope.h"
#include <cmath>


Rope::Rope(Player* p_1,Player* p_2) {
	m_p1 = p_1;
	m_p2 = p_2;
	
	m_sort_object = ROPE;
}


void Rope::Update() {
	PlayersDistanceAdjust();
}


void Rope::Draw() {
	static const float ROPE_LEGTH_ADJUST = 0.5f;
	static const float POS_OFFSET = 10.f;
	Texture::Draw2D(
		"Resource/Texture/Player/himo.png",
		m_p1->GetPos().x,
		m_p1->GetPos().y + POS_OFFSET,
		ROPE_LEGTH_ADJUST / LengthPercentage(),
		ROPE_LEGTH_ADJUST,
		AngleCalc()
	);
}


float Rope::AngleCalc() {
	static const float RAD = 180.f;
	// 弧度法に変換
	float angle = atan2((m_p2->GetPos().y - m_p1->GetPos().y) ,
		(m_p2->GetPos().x - m_p1->GetPos().x)) * (RAD / D3DX_PI);
	return angle;
}


float Rope::PlayersRadiusCalc() {
	// 2点間の距離算出
	float distance = ((
		(m_p2->GetPos().x - m_p1->GetPos().x) * 
		(m_p2->GetPos().x - m_p1->GetPos().x)) +
		((m_p2->GetPos().y - m_p1->GetPos().y) * 
		(m_p2->GetPos().y - m_p1->GetPos().y)));

	// 距離から半径算出
	float radius = sqrt(distance);

	return radius;
}


float Rope::LengthPercentage() {
	// 長さの比率を返す
	return MAX_ROPE_LEGTH / PlayersRadiusCalc();
}


void Rope::PlayersDistanceAdjust() {
	if (MAX_ROPE_LEGTH <= PlayersRadiusCalc()) {
		// HACK:PlayersRadiusCalc()がMAX_ROPE_LEGTHよりはみ出る
		if (m_p1->swim_enable == true || m_p2->swim_enable == false) {

		m_p2->GetPos() += m_p1->GetMove() + m_p2->GetMove();
		m_p2->SetPos(m_p2->GetPos());

		m_p1->SetMove({ 0, 0 });
		}
		if (m_p2->swim_enable == true || m_p1->swim_enable == false) {

		m_p1->GetPos() += m_p2->GetMove() + m_p1->GetMove();
		m_p1->SetPos(m_p1->GetPos());

		m_p2->SetMove({ 0, 0 });
		}
	}
}
