#include<time.h>
#include"EnemyManager.h"
#include"SeaUrchin.h"
#include"SellFish.h"
#include"../../Blind/Blind.h"


EnemyManager::EnemyManager(ObjectManager* obg_mng) {
	m_pobj_mng = obg_mng;
	// ランダム生成のためのシード値設定
	srand((unsigned int)time(nullptr));
}
//――――――――――――――――――――――――――

EnemyManager::~EnemyManager() {
	// 配列に要素が残っているものだけ削除
	for(auto &i:m_enemy_list){
		if (i != nullptr) {
			delete i;
		}
	}
}
//――――――――――――――――――――――――――

// 更新関数
void EnemyManager::Update() {
	Delete();
}
//―――――――――――――――――――――――――――

// 描画関数
void EnemyManager::Draw() {
	for (auto i : m_enemy_list) {
		if (i != nullptr) {
			// 各要素の描画処理
			i->Draw();
		}
	}
}
//―――――――――――――――――――――――――――

// 敵生成の関数
void EnemyManager::EnemyCreate(D3DXVECTOR2 pos, MapChip* map_chip) {
	if (m_enemy_list.size() < Enemy_Max_Num) {
		// 当たり判定の確認のため、不動ウニのみ生成してます。

		// 一定の確率で敵を生成
		//if (rand() % 100 == 0) {
		//	// ランダムに割り出したxyを使用して敵を登録
		//	m_enemy_list.emplace_back(new SeaUrchin(pos, map_chip));
		//	m_pobj_mng->Entry(m_enemy_list.back());
		//}
		//else if (rand() % 100 == 5) {
			m_enemy_list.emplace_back(new SeaUrchin(pos, map_chip, true));
			m_pobj_mng->Entry(m_enemy_list.back());
		//}
		//else if (rand() % 100 == 3) {
		//	m_enemy_list.emplace_back(new SellFish(pos, map_chip));
		//	m_pobj_mng->Entry(m_enemy_list.back());
		//}
	}
}
//―――――――――――――――――――――――――――

// ブラインド生成の関数
void EnemyManager::BlindCreate(D3DXVECTOR2 pos, D3DXVECTOR2 goal) {
		// Objectに登録時にブラインド用変数に代入、その後にブラインドを生成
		m_pobj_mng->Entry(m_pblind = new Blind);
		m_pblind->Create(pos, goal);
}
//―――――――――――――――――――――――――――

// 敵削除の関数
void EnemyManager::Delete() {
	// 削除ループ
	for (auto it = m_enemy_list.begin(); it != m_enemy_list.end();) {
		if ((*it)->IsActive() == false) {
			// 生成時に登録されているIdで、Object配列側の要素を指定
			m_pobj_mng->Exit((*it)->GetId());
			delete (*it);
			it = m_enemy_list.erase(it);
		}
		else {
			++it;
		}
	}
	if (m_pblind != nullptr && m_pblind->IsActive()==false) {
		m_pobj_mng->Exit(m_pblind->GetId());
		delete m_pblind;
		m_pblind = nullptr;
	}
}
//――――――――――――――――――――――――――――

// 生成している敵の総数を返す関数
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
