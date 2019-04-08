#pragma once
#include<string>
#include<vector>
#include"MapData.h"



class MapLoader {
public:

	// MapDataを生成して読み込みして取得
	MapData GetToLoadToCreateTheMapData(const std::string&map_name, const std::string&bg_name);

private:

	// ファイル名を受け取って使う
	void MapLoad(const std::string&map_name);

	// 背景レイヤー
	void BGLoad(const std::string&bg_name);
};