#include "Rope.h"
#include <cmath>


const float Rope::MAX_ROPE_LEGTH = 650.f;
const float Rope::ROPE_LEGTH_OFFSET = 0.5f;
const float Rope::POS_Y_OFFSET = 10.f;


//Rope::Rope(Player* p_1,Player* p_2) {
//	m_p1 = p_1;
//	m_p2 = p_2;
//	
//	m_sort_object_type = ROPE;
//}


Rope::Rope(PlayerManager*pm) {
	m_p_player_mng = pm;
	m_sort_object_type = ROPE;
}


void Rope::Update() {
	PlayersDistanceAdjust();
}


void Rope::Draw() {
	Texture::Draw2D(
		"Resource/Texture/Player/himo.png",
		m_p_player_mng->GetPosRelay(Player::STAR_1).x,
		m_p_player_mng->GetPosRelay(Player::STAR_1).y + POS_Y_OFFSET,
		ROPE_LEGTH_OFFSET / LengthPercentage(),
		ROPE_LEGTH_OFFSET,
		AngleCalc()
	);
}


float Rope::AngleCalc() {
	static const float RAD = 180.f;
	// 弧度法に変換
	float angle = atan2((m_p_player_mng->GetPosRelay(Player::STAR_2).y 
		- m_p_player_mng->GetPosRelay(Player::STAR_1).y) ,
		(m_p_player_mng->GetPosRelay(Player::STAR_2).x 
		- m_p_player_mng->GetPosRelay(Player::STAR_1).x)) * (RAD / D3DX_PI);
	return angle;
}


float Rope::PlayersRadiusCalc() {
	// 2点間の距離算出
	float distance =
		(((m_p_player_mng->GetPosRelay(Player::STAR_2).x
			- m_p_player_mng->GetPosRelay(Player::STAR_1).x)) *
		(m_p_player_mng->GetPosRelay(Player::STAR_2).x
			- m_p_player_mng->GetPosRelay(Player::STAR_1).x)) +
		((m_p_player_mng->GetPosRelay(Player::STAR_2).y
			- m_p_player_mng->GetPosRelay(Player::STAR_1).y) *
		(m_p_player_mng->GetPosRelay(Player::STAR_2).y
			- m_p_player_mng->GetPosRelay(Player::STAR_1).y));

	// 距離から半径算出
	float radius = sqrt(distance);

	return radius;
}


float Rope::LengthPercentage() {
	return MAX_ROPE_LEGTH / PlayersRadiusCalc();
}


void Rope::PlayersDistanceAdjust() {
	// 対の意味のif文を書きreturnで関数を終了させています（可読性向上のため）

	// どちらかの自機が死んでいるときは終了
	if (m_p_player_mng->IsActiveRelay(Player::STAR_1) != true || m_p_player_mng->IsActiveRelay(Player::STAR_2) != true) {
		return;
	}
	// プレイヤーの距離がロープの最大全長以下のときは終了
	if (MAX_ROPE_LEGTH > PlayersRadiusCalc()) {
		return;
	}
	// どちらかが初期値以外(重力は含む)の移動量を保持していなかった場合（泳いでいない自機がいる場合）
	if (m_p_player_mng->GetMoveRelay(Player::STAR_1) != D3DXVECTOR2(0.f, 1.f) || m_p_player_mng->GetMoveRelay(Player::STAR_2) != D3DXVECTOR2(0.f, 1.f)) {
		ToPlayersPull();
	}
}


void Rope::ToPlayersPull() {
	// 自機1のみ泳ぐとき
	if (m_p_player_mng->SwimEnableRelay(Player::STAR_1) == true || m_p_player_mng->SwimEnableRelay(Player::STAR_2) == false) {
		// 1の進みたい方向に自機2がいるとき、2に1の移動量を加算
		if (m_p_player_mng->PartnerIsThereDirection(Player::STAR_1, Player::STAR_2) == true) {
			m_p_player_mng->SetMoveRelay(Player::STAR_2, m_p_player_mng->GetMoveRelay(Player::STAR_1)+ m_p_player_mng->GetMoveRelay(Player::STAR_2));
		}
	}
	// 自機2のみ泳ぐとき
	if (m_p_player_mng->SwimEnableRelay(Player::STAR_1) == false || m_p_player_mng->SwimEnableRelay(Player::STAR_2) == true) {
		// 2の進みたい方向に自機1がいるとき、1に2の移動量を加算
		if (m_p_player_mng->PartnerIsThereDirection(Player::STAR_2, Player::STAR_1) == true) {
			m_p_player_mng->SetMoveRelay(Player::STAR_1, m_p_player_mng->GetMoveRelay(Player::STAR_1)+ m_p_player_mng->GetMoveRelay(Player::STAR_2));
		}
	}
	// 両方の自機が泳ぐとき
	if (m_p_player_mng->SwimEnableRelay(Player::STAR_1) == true && m_p_player_mng->SwimEnableRelay(Player::STAR_2) == true) {
		// X方向の移動量を消すことでロープの最大距離で2体の距離を維持する
		m_p_player_mng->SetMoveRelay(Player::STAR_1, { 0.f , m_p_player_mng->GetMoveRelay(Player::STAR_1).y });
		m_p_player_mng->SetMoveRelay(Player::STAR_2, { 0.f , m_p_player_mng->GetMoveRelay(Player::STAR_2).y });
	}
}

