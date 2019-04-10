#pragma once
#include<string>
#include<vector>




// マップ関連の情報をいれるラッパークラス
class MapData {
public:

	MapData(const std::string&map_name,
		int index_x, int index_y, int chip) {

		m_map_name = map_name;
	};

	MapData() {};

	void SetMapName(const std::string&map_name) {
		m_map_name = map_name;
	}

	void SetMapChip(int index_x, int index_y, int chip) {
		m_map_chip[index_y][index_x] = chip;
	}

	// マップファイル名を返す
	std::string GetMapName() {
		return m_map_name;
	}

private:
	// 初期化時に生成
	std::string m_map_name;     // マップを読み込むファイル名
	int m_map_chip[1000][1000]; // マップのチップ 
};