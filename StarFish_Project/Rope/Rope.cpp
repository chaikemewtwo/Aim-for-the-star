#include "Rope.h"
#include <cmath>


const float Rope::MAX_ROPE_LEGTH = 650.f;
const float Rope::ROPE_LEGTH_OFFSET = 0.5f;
const float Rope::POS_Y_OFFSET = 10.f;


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
	// 対の意味のif文を書きreturnで関数を終了させています（可読性向上のため）

	// どちらかが死んでいるときは終了
	if (m_p1->IsActive() != true || m_p2->IsActive() != true) {
		return;
	}
	// プレイヤーの距離がロープの最大全長以下のときは終了
	if (MAX_ROPE_LEGTH > PlayersRadiusCalc()) {
		return;
	}
	// どちらかが初期値以外(重力は含む)の移動量を保持していなかった場合（泳いでいない自機がいる場合）
	if (m_p1->GetMove() != D3DXVECTOR2(0.f, 1.f) || m_p2->GetMove() != D3DXVECTOR2(0.f, 1.f)) {
		ToPlayersPull();
	}
}


void Rope::ToPlayersPull() {
	// 自機1のみ泳ぐとき
	if (m_p1->SwimEnable() == true || m_p2->SwimEnable() == false) {
		if (PartnerIsThereDirection(m_p1, m_p2) == true) {
			m_p2->SetMove(m_p1->GetMove() + m_p2->GetMove());
		}
	}
	// 自機2のみ泳ぐ
	if (m_p1->SwimEnable() == false || m_p2->SwimEnable() == true) {
		if (PartnerIsThereDirection(m_p2, m_p1) == true) {
			m_p1->SetMove(m_p2->GetMove() + m_p1->GetMove());
		}
	}
	// 両方の自機が泳ぐ
	if (m_p1->SwimEnable() == true && m_p2->SwimEnable() == true) {
		m_p1->SetMoveX(0.f);
		m_p2->SetMoveX(0.f);
	}
}


bool Rope::PartnerIsThereDirection(Player*myself, Player*partner) {
	// p1のX移動量がp1の座標から見て正の方向、p1の自機から見てp2の自機が正の方向
	if (myself->GetMove().x < 0.f && myself->GetPos().x < partner->GetPos().x) {
		return true;
	}
	// p1のX移動量がp1の座標から見て負の方向、p1の自機から見てp2の自機が負の方向
	else if (myself->GetMove().x > 0.f && myself->GetPos().x > partner->GetPos().x) {
		return true;
	}
	else {
		return false;
	}
}
