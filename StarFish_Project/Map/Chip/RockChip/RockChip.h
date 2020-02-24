#pragma once
#include"../../../GameObject/Object/Object.h"
#include<string>
#include"../ChipBase/ChipBase.h"



// 岩盤チップの型

//  番号   岩盤の種類
//	1,   // 左上
//	2,   // 右上
//	3,	 // 左下
//	4,	 // 右下
//	5,	 // 右
//	6,	 // 左
//	7,	 // 上
//	8,	 // 下
//	9,   // 中央
//	10,  // アンモナイト
//};

// ================================================
/**
* @file RockChip.h
* @brief 岩盤オブジェクトを管理しているファイル
* @author maekawa
*/
// ================================================


// 前方参照
class Map;


/**
* @brief 岩盤クラス
*/
class RockChip : public ChipBase{
public:


	/**
	* @brief RockChipクラスのコンストラクタ
	* @details コンストラクタでどのチップを使うか決める
	*/
	RockChip(int chip_num,const D3DXVECTOR2 &pos,Map*map);


	/**
	* @brief 描画(Object.h In override)
	*/
	void Draw()override;


	/**
	* @brief 更新(Object.h In override)
	*/
	void Update()override;
	

private:

	//! 岩盤の最大チップ数	       
	static const int MAX_CHIP = 10;

private:

	//! 岩盤文字列
	std::string bed_rock_chip_name;

	//! マップインスタンス
	Map * m_p_map;
};
