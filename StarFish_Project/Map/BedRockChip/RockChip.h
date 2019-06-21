#pragma once
#include"../../GameObject/Object/Object.h"
#include<string>


/* HACK まだできていません */

// 岩盤チップの型
//enum BedRockChipType {
//	LEFT_UP,		 // 左上
//	RIGHT_UP,		 // 右上
//	LEFT_DOWN,		 // 左下
//	RIGHT_DOWN,		 // 右下
//	RIGHT,			 // 右
//	LEFT,			 // 左
//	UP,				 // 上
//	DOWN,			 // 下
//	CENTER,          // 中央
//	CENTER_AMMONITE, // アンモナイト
//};

// 前方参照
class Map;

// 岩盤クラス
class RockChip : public Object{
public:

	// コンストラクタでどのチップを使うか決める
	RockChip(int chip_num,const D3DXVECTOR2 &pos,Map*map);

	void Draw()override;
	void Update()override;

private:

	// 岩盤の最大チップ数	       
	static const int MAX_CHIP = 10;

private:

	float chip_u[10]; // 線を直す為にずらすUV用配列U
	float chip_v[10]; // 線を直す為にずらすUV用配列V

	// 岩盤文字列
	std::string bed_rock_chip_name;
	const char *str_buf[MAX_CHIP];
	// 岩盤チップをずらす座標
	D3DXVECTOR2 offset[MAX_CHIP];
	
	Map*m_map;
};
