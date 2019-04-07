#pragma once
#include"MapData.h"

// マップ生成抽象ベース
class MapBase {
public:

	// コンストラクタで入れる
	MapBase(MapData*md) {
		pm_md = md;
	}

	~MapBase() {
		// マップが消えたらマップデータも消えるようにしたい
		delete pm_md;
	}

	// 描画関数
	void MapDraw(int y, int x, int h,MapData&map_data) {

	}

	virtual void Draw() {};

protected:

	MapData * pm_md;
};