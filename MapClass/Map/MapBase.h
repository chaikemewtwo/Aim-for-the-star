﻿#pragma once
#include<string>



// マップ生成抽象ベース
class MapBase {
public:

	// コンストラクタで入れる
	MapBase() {

	}

	virtual ~MapBase() {}

	// マップ読み込み
	void MapLoad(const std::string&file_name);

	// マップの更新
	virtual void ObjectCreateUpdate() {};

protected:

	// マップ配列
	int chip[1000][1000];
};