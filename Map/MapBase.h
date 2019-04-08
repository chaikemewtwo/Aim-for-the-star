#pragma once
#include"MapData.h"

// マップ生成抽象ベース
class MapBase {
public:

	// コンストラクタで入れる
	MapBase(MapData*md) {
		pm_md = md;

		// 初期化
		pm_obj = new MapObject;
		pm_bg = new BackGround(pm_md);
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

	// マップに必要な情報
	MapObject * pm_obj;
	BackGround * pm_bg;
	MapData * pm_md;
};