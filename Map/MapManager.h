#pragma once
#include"SeaMap.h"
#include"MapBase.h"
#include"MapLoader.h"
#include"BackGround.h"
#include"../MapObject.h"
#include<vector>
#include<memory>


// ここで使うマップを決める。


// マップ管理
class MapManager {
public:

	MapManager() {

		// 初期化
		m_map_obj = new MapObject;
		m_bg = new BackGround;
		m_map_loader = new MapLoader;
	}

	// マップ生成
	void MapCreate(MapBase&mb, std::string&map_file_name, std::string&bg_file_name);

	void Update();

private:
	MapBase *m_map_base;         // マップの選択

	MapObject*m_map_obj;         // マップのオブジェクト管理
	BackGround*m_bg;             // 背景
	MapLoader*m_map_loader;      // マップ読み込み
};