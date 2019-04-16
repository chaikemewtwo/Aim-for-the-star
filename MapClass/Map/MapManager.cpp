#include"MapManager.h"





MapManager::MapManager() {
	
	m_pbg = new BackGround;
	m_psea_map = new SeaMap;

	//m_pbg->BGLoad("Map");
}

MapManager::~MapManager() {

	// マップデータが入っている場合は削除する
	if (m_psea_map != nullptr) {

		m_psea_map = nullptr;
		delete m_psea_map;
	}
}


void MapManager::Update() {

	if (m_psea_map != nullptr) {
		return;
	}

	// 描画
	m_psea_map->Update();
	m_pbg->Update();
}

void MapManager::Draw() {

	m_pbg->Draw();
}
