#include "Rope.h"
#include <cmath>


Rope::Rope(Player* p_1,Player* p_2) {
	m_p1 = p_1;
	m_p2 = p_2;
	
	m_sort_object_type = ROPE;
}


void Rope::Update() {
	// 常時距離調整
	// HACK:PlayerManagerを作成しそこで行う
	PlayersDistanceAdjust();
}


void Rope::Draw() {
	// ロープ最大全長調整
	static const float ROPE_LEGTH_OFFSET = 0.5f;
	// 描画Y軸調整
	//（自機の中心より少し下に変更、死亡状態でヒモの先端が見えてしまうため）
	static const float POS_Y_OFFSET = 10.f;

	Texture::Draw2D(
		"Resource/Texture/Player/himo.png",
		m_p1->GetPos().x,
		m_p1->GetPos().y + POS_Y_OFFSET,
		ROPE_LEGTH_OFFSET / LengthPercentage(),
		ROPE_LEGTH_OFFSET,
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
