#include"MapManager.h"



MapManager::MapManager(Player*p,EnemyManager*e_mng) {
	
	// 背景1
	m_pbg = new BackGround("Map/BGData/BG1.csv",p);
	// マップチップ
	m_pmap_tip = new MapTip(p,e_mng);
	// 背景2
	m_pbg2 = new BackGround("Map/BGData/BG2.csv",p);
	// インスタンスを持たせる
	m_pp = p;
}


MapManager::~MapManager() {

	// マップデータが入っている場合は削除する
	if (m_pmap_tip != nullptr) {

		// マップの削除
		m_pmap_tip = nullptr;
		delete m_pmap_tip;
	}
}


void MapManager::Update() {

	// nullチェック
	if (m_pmap_tip == nullptr) {
		return;
	}
	if (m_pbg == nullptr) {
		return;
	}

	// マップ関連更新
	m_pmap_tip->Update();
	m_pbg->Update();
}

void MapManager::Draw() {

	// 描画
	m_pbg->Draw();
	m_pmap_tip->Draw();
}
