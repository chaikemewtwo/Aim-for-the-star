#include"EnemyManager.h"
#include"SeaUrchin.h"
#include"SellFish.h"


EnemyManager::EnemyManager(ObjectManager* obg_mng) {
	m_p_obj_mng = obg_mng;
}
//――――――――――――――――――――――――――

EnemyManager::~EnemyManager() {

	// 配列に要素が残っているものだけ削除
	for (auto &enemy : m_enemy_list) {

		if (enemy != nullptr) {
			delete enemy;
		}
	}
}
//――――――――――――――――――――――――――

void EnemyManager::Update() {
	DeleteCheck();
}
//―――――――――――――――――――――――――――

void EnemyManager::Draw() {

	for (auto enemy : m_enemy_list) {

		if (enemy != nullptr) {
			enemy->Draw();
		}
	}
}
//―――――――――――――――――――――――――――

void EnemyManager::CreateEnemy(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2, EnemyType type_num) {

	switch (type_num) {

	case SEAURCHIN:
		m_enemy_list.emplace_back(new SeaUrchin(pos, map));
		break;

	case NO_MOVE_SEAURCHIN:
		m_enemy_list.emplace_back(new SeaUrchin(pos, map, false));
		break;

	case SELLFISH:
		m_enemy_list.emplace_back(new SellFish(pos, map, p1, p2));
		break;
	}

	// 生成された敵をObjectManagerに登録
	m_p_obj_mng->Entry(m_enemy_list.back());
}
//―――――――――――――――――――――――――――

void EnemyManager::CreateBlind(D3DXVECTOR2 pos, D3DXVECTOR2 goal) {

	// Objectに登録時にブラインド用変数に代入、その後にブラインドを生成
	m_p_obj_mng->Entry(m_p_blind = new Blind);
	m_p_blind->Create(pos, goal);
}
//―――――――――――――――――――――――――――

void EnemyManager::DeleteCheck() {

	// 削除ループ
	for (auto itr = m_enemy_list.begin(); itr != m_enemy_list.end();) {

		if ((*itr)->IsActive() == false) {

			// 生成時に登録されているIdで、Object配列側の要素を指定
			m_p_obj_mng->Exit((*itr)->GetId());
			delete (*itr);
			itr = m_enemy_list.erase(itr);
		}
		else {
			++itr;
		}
	}
	if (m_p_blind != nullptr && m_p_blind->IsActive()==false) {

		m_p_obj_mng->Exit(m_p_blind->GetId());
		delete m_p_blind;
		m_p_blind = nullptr;
	}
}
//――――――――――――――――――――――――――――

int EnemyManager::GetEnemyTotal() {
	return m_enemy_list.size();
}
//――――――――――――――――――――――――――――

EnemyBase* EnemyManager::GetEnemyInstance(int num) {

	if (m_enemy_list[num] != nullptr) {
		return m_enemy_list[num]->GetInstance();
	}

	return nullptr;
}
//――――――――――――――――――――――――――――
