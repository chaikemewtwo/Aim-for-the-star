#pragma once
#include"../../GameObject/Object/Object.h"
#include"../../Lib/Window/Window.h"


// MEMO
// MapManagerでBackGroundの変更を加えた


class Map; //マップの前方参照

// 背景クラス
class BackGround : public Object{
public:

	// ファイル名とスクロールする位置の参照をいれる。
	BackGround(
		const std::string&file_name,
		Map*map,SortObject sort_num,
		float graph_scale_x = -50.f,
		float graph_scale_y = 0.f,
	bool scroll_limit = true);

	void Update();
	void Draw();
	
	float GetMaxMapPos()const;
	bool IsMaxScroll()const;

private:

	static constexpr int GRAPH_DIFFERENCE = 50;       // 背景の端数
	static constexpr float BG_CHANGE_LINE = 10.f; // 背景が入れ替わる範囲

private:
	
	/* private関数 */
	void MoveAdd();                           // 自機を取り入れる
	void BGLoad(const std::string&file_name); // 背景の読み込み
	void Scroll();                            // 背景スクロール
	void PosAdd();                            // 位置更新
	bool IsDownScrollLimit();                 // スクロール制限下
	bool IsUpScrollLimit();                   // スクロール制限上

private:

	/* 背景読み込み用バッファ */
	std::vector<const char*>m_pback_str;      // 背景文字列
	char str_load_buf[1000][500];             // 読み込み専用のもの
											  
	/* 背景	*/							   	  
	//D3DXVECTOR2 m_pos;                      // 背景遷移判定上
	D3DXVECTOR2 m_move;                       // 移動ベクトル
	int m_max_graph_num;				      // 画像の最大数  
	int m_current_pos;                        // 今いる位置
	int m_connect1_graph;                     // 連結画像1 
	int m_connect2_graph;                     // 連結画像2
	int m_h_difference;                       // 縦の画像の端数
	int m_w_difference;                       // 横の画像の端数
	float m_h_graph_difference;               // 高さの背景画像の端数
	float m_w_graph_difference;				  // 横の背景画像の端数
	bool m_is_max_scroll;                     // スクロール位置の最大値
	bool m_is_scroll_limit;

	/* マップインスタンス */
	Map *m_pmap;
};
