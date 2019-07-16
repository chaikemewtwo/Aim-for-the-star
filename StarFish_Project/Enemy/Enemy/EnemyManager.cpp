#include"EnemyManager.h"
#include"SeaUrchin.h"
#include"SellFish.h"
#include"NaporeonFish.h"


EnemyManager::EnemyManager(ObjectManager* const obg_mng) {
	m_p_obj_manager = obg_mng;
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
	// 削除するかのチェック
	CheckDelete();
}
//―――――――――――――――――――――――――――

// 指定された敵を指定の位置に生成する
void EnemyManager::CreateEnemy(const D3DXVECTOR2 pos, Map* const map, PlayerManager* const p_mng, const EnemyType type_num) {

	switch (type_num) {

	case EnemyType::SEAURCHIN:
		m_enemy_list.emplace_back(new SeaUrchin(pos, map));
		break;

	case EnemyType::NO_MOVE_SEAURCHIN:
		m_enemy_list.emplace_back(new SeaUrchin(pos, map, false));
		break;

	case EnemyType::SELLFISH:
		m_enemy_list.emplace_back(new SellFish(pos, map, p_mng));
		break;

	case EnemyType::NAPOREONFISH:
		m_enemy_list.emplace_back(new NaporeonFish(pos, map, p_mng));
		break;
	}

	// 生成された敵をObjectManagerに登録
	m_p_obj_manager->Entry(m_enemy_list.back());
}
//―――――――――――――――――――――――――――

// 指定の位置にブラインドを生成する
void EnemyManager::CreateBlind(const D3DXVECTOR2 from, const D3DXVECTOR2 goal) {

	// Objectに登録時にブラインド用変数に代入、その後にブラインドを生成
	m_p_obj_manager->Entry(m_p_blind = new Blind);
	m_p_blind->Create(from, goal);
}
//―――――――――――――――――――――――――――

// Activeフラグがfalseのものを削除する
void EnemyManager::CheckDelete() {

	// 敵の削除ループ
	for (auto itr = m_enemy_list.begin(); itr != m_enemy_list.end();) {

		if ((*itr)->IsActive() == false) {

			// 生成時に登録されているIdで、Object配列側の要素を指定
			m_p_obj_manager->Exit((*itr)->GetId());
			delete (*itr);
			itr = m_enemy_list.erase(itr);
		}
		else {
			++itr;
		}
	}

	// ブラインドの削除
	if (m_p_blind != nullptr && m_p_blind->IsActive()==false) {

		// Objectのリストから削除後、ブラインド自体を削除する
		m_p_obj_manager->Exit(m_p_blind->GetId());
		delete m_p_blind;
		m_p_blind = nullptr;
	}
}
//――――――――――――――――――――――――――――

// 敵の配列の数を返す
int EnemyManager::GetEnemyTotal()const {
	return m_enemy_list.size();
}
//――――――――――――――――――――――――――――

// 指定された敵のインスタンスを返す関数を呼び出す
EnemyBase* EnemyManager::GetEnemyInstance(const int num) {

	if (m_enemy_list[num] != nullptr) {
		return m_enemy_list[num]->GetInstance();
	}

	return nullptr;
}
//――――――――――――――――――――――――――――
