#include"MapManager.h"




void MapManager::Update() {

	if (m_pmap_base != nullptr) {
		return;
	}

	// 描画
	m_pmap_base->Update();
	m_pbg->Update();
}
