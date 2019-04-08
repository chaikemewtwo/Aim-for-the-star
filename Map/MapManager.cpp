#include"MapManager.h"





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

	// データ読み込み
	MapData*md = &m_map_loader->GetToLoadToCreateTheMapData(map_file_name, bg_file_name);

	// マップを選ぶ
	m_map_base = new SeaMap(md);
	// 背景を選ぶ(こちらはEntry関数)
	m_bg = new BackGround(md);
}


