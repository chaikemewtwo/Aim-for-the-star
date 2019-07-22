#pragma once
#include"../../GameObject/Object/Object.h"
#include"../../Lib/Window/Window.h"
#include"../Map/Map.h"



// =============================
/**
* @file BackGround.h
* @brief 背景関連ファイル
* @author maekawa
*/
// =============================


/* =============================
  背景動作説明

  背景は今現在いる場所1枚と上か下
　画像サイズを入れると、自ずと画面の中心に描画されるようになっている。

   ============================= */


/**
* @brief 背景クラス
*/
class BackGround : public Object{
public:

	//! 背景の最大画像数
	static constexpr int MAX_BACKGROUND_GRAPH = 5;  

	//! 上の最大スクロール
	static constexpr float MAX_UP_SCROLL = (Map::CHIP_SIZE * 18) * MAX_BACKGROUND_GRAPH + 1170;

public:

	/**
	* @brief 背景クラスのコンストラクタ(ファイル名とスクロールする位置の参照をいれる)
	* @param[in] 読み込むテキストファイル名
	* @param[out] Mapのインスタンスを入れる
	* @param[in] ソート型を入れる
	* @param[in] 横の背景画像サイズを入れる
	* @param[in] 縦の背景画像サイズを入れる
	*/
	BackGround(
		const std::string&text_file_name,
		Map*map,
		SortObjectType sort_num,
		float graph_width_scale = -50.f,
		float graph_height_scale = 0.f);


	/**
	* @brief デストラクタ
	*/
	~BackGround();


	/**
	* @brief 更新(override)
	*/
	void Update();


	/**
	* @brief 描画(override)
	*/
	void Draw();

	
	/**
	* @brief マップの最大値を返す
	* @return float マップの最大値
	*/
	float GetMaxMapPos()const;


private:
	
	// 背景の端数
	static constexpr int GRAPH_DIFFERENCE = 50;
	// 背景が入れ替わる範囲
	static constexpr float BG_CHANGE_LINE = 10.f;
	
private:
	
	/**
	* @brief 移動値を加算
	*/
	void MoveSub();                           


	/**
	* @brief 移動調整する
	*/
	void MoveAdjustment(int adjustment_num);  


	/**
	* @brief 背景の読み込み
	*/
	void BGLoad(const char*file_name);        


	/**
	* @brief 背景スクロール
	* @detail 描画には画面分のシート画像があり、それを前後に配置しながらスクロールしていく
	* @detail 通り過ぎたシート画像は描画されないようになっている
	*/
	void Scroll();


	/**
	* @brief Y座標加算
	*/
	void PosYToMoveYAdd();


	/**
	* @brief スクロールするかどうか
	* @return bool スクロールしても良いならtrue,いけないならfalseを返す
	*/
	bool IsScroll();


private:

	//! 背景読み込み用バッファ
	std::vector<char*>m_p_bg_file_name_list;      
									
	//! 移動ベクトル
	D3DXVECTOR2 m_move;                

	//! 画像の最大数 
	int m_max_graph_num;				

	//! 連結画像1 
	int m_connect1_graph;         

	//! 連結画像2
	int m_connect2_graph;      

	//! 縦の画像の端数
	int m_height_graph_difference;  

	//! 横の画像の端数
	int m_width_graph_difference;   

	//! 画像の縦のサイズ端数
	float m_height_graph_size_differance; 

	//! マップポインタ
	Map *m_p_map;
};
