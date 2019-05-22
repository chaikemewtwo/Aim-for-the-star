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
			i->Draw();
		}
	}
}
//―――――――――――――――――――――――――――

// 敵生成の関数
void EnemyManager::EnemyCreate(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2, EnemyType type_num) {
	// 1～3の数値をランダムに選出《処理を変更予定》
	/*
	マップチップを受け取って、その数値によって生成する敵の種類を変更する。
	例）if(mapchip_num > 100) { ほら貝生成; }
	    else if(mapchip_num >50 && mapchip_num <100) { ウニ生成; }
	*/

	switch (type_num) {
	case SEAURCHIN:
		m_enemy_list.emplace_back(new SeaUrchin(pos, map));
		m_pobj_mng->Entry(m_enemy_list.back());
		break;
	case NO_MOVE_SEAURCHIN:
		m_enemy_list.emplace_back(new SeaUrchin(pos, map, true));
		m_pobj_mng->Entry(m_enemy_list.back());
		break;
	case SELLFISH:
		m_enemy_list.emplace_back(new SellFish(pos, map, p1, p2));
		m_pobj_mng->Entry(m_enemy_list.back());
		break;
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
