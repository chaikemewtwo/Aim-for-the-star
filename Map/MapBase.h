#pragma once
#include"MapData.h"

// マップ生成抽象ベース
class MapBase {
public:

	void MapDraw(int y, int x, int h,MapData&map_data) {

	}

	// マップの変更
	virtual MapBase* ChangeStage() = 0;
};