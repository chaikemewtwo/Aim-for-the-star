#pragma once
#include"../StarFish_Project/GameObject/Object/Object.h"
#include<string>

/* HACK まだできていません */

// 岩盤チップの型
enum BedRockChipType {
	LEFT_UP,		 // 左上
	RIGHT_UP,		 // 右上
	LEFT_DOWN,		 // 左下
	RIGHT_DOWN,		 // 右下
	RIGHT,			 // 右
	LEFT,			 // 左
	UP,				 // 上
	DOWN,			 // 下
	CENTER,          // 中央
	CENTER_AMMONITE, // アンモナイト
};


// 岩盤クラス
class BedRockChip : public Object{
public:

	// コンストラクタでどのチップを使うか決める
	BedRockChip(const std::string&str,const D3DXVECTOR2 &pos);

	void Draw()override;
	void Update()override;

private:

	// 岩盤文字列
	std::string str_buf;
};
