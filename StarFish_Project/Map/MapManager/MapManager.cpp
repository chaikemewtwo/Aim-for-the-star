#include"MapManager.h"
#include"../../Player/Player.h"
#include"../MapChip/MapChip.h"


MapManager::MapManager(Player*star1,Player*star2,EnemyManager*e_mng) {
	
	// マップチップ
	m_pmap_tip = new MapChip(star1,star2,e_mng);
	// 背景1
	m_pbg = new BackGround("Map/BGData/BG1.csv", m_pmap_tip);
	// 背景2
	m_pbg2 = new BackGround("Map/BGData/BG2.csv",m_pmap_tip);
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
