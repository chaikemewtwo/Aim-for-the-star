#include"PlayerManager.h"


const D3DXVECTOR2 PlayerManager::STAR_1_FIRST_POS = { Window::WIDTH / 2.f - 200.f, Window::HEIGHT / 2.f + 200.f };
const D3DXVECTOR2 PlayerManager::STAR_2_FIRST_POS = { Window::WIDTH / 2.f + 200.f, Window::HEIGHT / 2.f + 200.f };


PlayerManager::PlayerManager(ObjectManager* obg_mng) {
	m_p_list[Player::STAR_1] = new Player(Player::STAR_1, STAR_1_FIRST_POS);
	m_p_list[Player::STAR_2] = new Player(Player::STAR_2, STAR_2_FIRST_POS);

	obg_mng->Entry(m_p_list[Player::STAR_1]);
	obg_mng->Entry(m_p_list[Player::STAR_2]);
}


PlayerManager::~PlayerManager() {
	//delete[] m_p_list;
}


void PlayerManager::Update() {
	//m_p_list[Player::STAR_1]->Update();
	//m_p_list[Player::STAR_2]->Update();

	// 片方死んだら片方も死ぬ
	if (m_p_list[Player::STAR_1]->IsActive() == false || m_p_list[Player::STAR_2]->IsActive() == false) {
		m_p_list[Player::STAR_1]->EnableDead();
		m_p_list[Player::STAR_2]->EnableDead();
	}
}


//void PlayerManager::Draw() {
//	m_p_list[Player::STAR_1]->Draw();
//	m_p_list[Player::STAR_2]->Draw();
//}


float PlayerManager::StaminaParcentageRelay(Player::ID_TYPE type) {
	return m_p_list[type]->StaminaParcentage();
}


D3DXVECTOR2 PlayerManager::GetPosRelay(Player::ID_TYPE type) {
	return m_p_list[type]->GetPos();
}


void PlayerManager::SetPosRelay(Player::ID_TYPE type, D3DXVECTOR2 new_pos) {
	m_p_list[type]->SetPos(new_pos);
}


D3DXVECTOR2 PlayerManager::GetMoveRelay(Player::ID_TYPE type) {
	return m_p_list[type]->GetMove();
}


void PlayerManager::SetMoveRelay(Player::ID_TYPE type, D3DXVECTOR2 new_move) {
	m_p_list[type]->SetMove(new_move);
}


bool PlayerManager::IsActiveRelay(Player::ID_TYPE type) {
	return m_p_list[type]->IsActive();
}


bool PlayerManager::SwimEnableRelay(Player::ID_TYPE type) {
	return m_p_list[type]->SwimEnable();
}


bool PlayerManager::PartnerIsThereDirection(Player::ID_TYPE myself, Player::ID_TYPE partner) {
	// myselfのX移動量がmyselfの座標から見て正の方向、myselfの自機から見てpartnerの自機が正の方向
	if (GetMoveRelay(myself).x < 0.f && GetPosRelay(myself).x < GetPosRelay(partner).x) {
		return true;
	}
	// myselfのX移動量がmyselfの座標から見て負の方向、myselfの自機から見てpartnerの自機が負の方向
	else if (GetMoveRelay(myself).x > 0.f && GetPosRelay(myself).x > GetPosRelay(partner).x) {
		return true;
	}
	return false;
}


Player* PlayerManager::GetPlayerInstance(int player_num) {

	if (m_p_list[player_num] != nullptr) {
		return m_p_list[player_num]->GetInstance();
	}

	return nullptr;
}
