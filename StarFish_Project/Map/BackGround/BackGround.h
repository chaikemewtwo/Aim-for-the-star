#pragma once
#include"../../GameObject/Object/Object.h"
#include"../../Lib/Window/Window.h"
#include"../MapChip/MapChip.h"

// MEMO
// MapManagerでBackGroundの変更を加えた



// 背景クラス
class BackGround : public Object{
public:

	// 背景の最大画像数
	static constexpr int MAX_BACKGROUND_GRAPH = 5;  
	// 上の最大スクロール
	static constexpr float MAX_UP_SCROLL = (Map::CHIP_SIZE * 18) * MAX_BACKGROUND_GRAPH + 1170;

	// ファイル名とスクロールする位置の参照をいれる。
	BackGround(
		const std::string&file_name,
		Map*map,SortObject sort_num,
		float graph_scale_x = -50.f,
		float graph_scale_y = 0.f);

	void Update();
	void Draw();
	
	float GetMaxMapPos()const;

private:
	
	static constexpr int GRAPH_DIFFERENCE = 50;       // 背景の端数
	static constexpr float BG_CHANGE_LINE = 10.f;     // 背景が入れ替わる範囲
	
private:
	
	/* private関数 */
	void MoveSub();                           // 自機を取り入れる
	void MoveAdjustment(int adjustment_num);  // 移動調整
	void BGLoad(const std::string&file_name); // 背景の読み込み
	void Scroll();                            // 背景スクロール
	void PosYToMoveYAdd();                    // Y位置更新
	bool IsScroll();                          // スクロールするかどうか

private:

	/* 背景読み込み用バッファ */
	std::vector<const char*>m_pback_str;      // 背景文字列
	//char str_load_buf[1000][500];           // 読み込み専用のもの
									
	D3DXVECTOR2 m_move;                       // 移動ベクトル
	int m_max_graph_num;				      // 画像の最大数  
	int m_current_pos;                        // 今いる位置
	/* 連結画像パラメータ */
	int m_connect1_graph;                     // 連結画像1 
	int m_connect2_graph;                     // 連結画像2
	/* 画像の端数 */
	int m_height_difference;                  // 縦の画像の端数
	int m_width_difference;                   // 横の画像の端数
	/* 画像を中央にずらす為の端数 */
	float m_graph_height_size_differance;     // 画像の縦のサイズ端数

	/* マップインスタンス */
	Map *m_pmap;
};
