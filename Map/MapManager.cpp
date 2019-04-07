#include"./Map/MapManager.h"





void MapManager::Update() {

	if (m_map_base != nullptr) {
		return;
	}

	// 描画
	m_map_base->Draw();
}

// マップ生成
void MapManager::MapCreate(MapBase&mb, std::string&map_file_name, std::string&bg_file_name) {

	// マップデータが入っている場合は削除する
	if (m_map_base != nullptr) {

		m_map_base = nullptr;
		delete m_map_base;
	}

	// セッターにして外部で設定できた方がいいかも
	// マップを選ぶ
	m_map_base = new SeaMap(&m_map_loader->GetToLoadToCreateTheMapData(map_file_name, bg_file_name));
}


