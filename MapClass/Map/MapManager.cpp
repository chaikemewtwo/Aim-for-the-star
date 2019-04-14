#include"MapManager.h"




MapManager::MapManager() {
	
	m_pbg = new BackGround;
	m_pmap_base = new SeaMap;

	//m_pbg->BGLoad("Map");
}

MapManager::~MapManager() {

	// マップデータが入っている場合は削除する
	if (m_pmap_base != nullptr) {

		m_pmap_base = nullptr;
		delete m_pmap_base;
	}
}


void MapManager::Update() {

	if (m_pmap_base != nullptr) {
		return;
	}

	// 描画
	m_pmap_base->ObjectCreateUpdate();
	m_pbg->Update();
}

void MapManager::Draw() {

	m_pbg->Draw();
}
