#pragma once
#include"SeaMap.h"
#include"MapBase.h"
#include"MapLoader.h"
#include"BackGround.h"
#include<vector>
#include<memory>



// マップ管理
class MapManager {
public:

	MapManager() {

		// 初期化
		m_bg = new BackGround;
		m_map_loader = new MapLoader;
	}

	// ファイルの名前を入れる
	void SetMapName(const std::string&map_name) {

		// 初期化をちゃんと行う
		if (m_map_name.empty != 0) {
			m_map_name.clear();
			m_map_name.shrink_to_fit();
		}

		// ここでLoad関数を呼ぶ
		m_map_loader
		
		// 文字列代入
		m_map_name = map_name;
	}

	void Update() {
		
		for (auto&itr : m_map_lists) {

			// ステージの入れ替えはマップの入れ替え
			 m_map_base = itr->ChangeStage();

			 if (m_map_base == NULL) {
				 break;
			 }
		}
	}

private:

	std::vector<std::unique_ptr<MapBase>>m_map_lists;
	MapBase*m_map_base;
	std::string m_map_name;
	BackGround*m_bg;            // 背景
	MapLoader*m_map_loader;     // マップ読み込み
};