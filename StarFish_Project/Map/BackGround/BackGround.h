#pragma once
#include"../../GameObject/Object/Object.h"

/*

Objectを変更するセッターを作るべき
誰の座標を使っているかを知る必要がある

*/

class Map; //マップの前方参照

// 背景クラス
class BackGround : public Object{
public:

	// 背景の大きさ
	static const int GRAPH_SCALE_H = 1180;
	static const int GRAPH_SCALE_W = 1920;

	// ファイル名とスクロールする位置の参照をいれる。
	BackGround(const std::string&file_name,Map*map,SortObject sort_num,float x = -50.f, float y = 0.f, int difference = 50);

	void Update();
	void Draw();

private:

	// constexprはコンパイル時定数になる
	//static const int GRAPH_NUM = 10;
	// 背景の端数
	static const int GRAPH_DIFFERENCE = 50;
	// 背景が入れ替わる範囲
	static constexpr float BG_CHANGE_LINE = 10.f;

private:
	// 自機を取り入れる
	void MovePosUpdate();

	// 背景の読み込み
	void BGLoad(const std::string&file_name);

	// 背景スクロール
	void Scroll();

	// 位置更新
	void PosUpdate();

	// 地面に着地
	bool LandOnTheGround();


	std::vector<const char*>m_pback_str;// 真背景文字列
	//const char* m_pback_str[GRAPH_NUM]; // 背景文字列
	char str_load_buf[1000][500];      // 読み込み専用のもの
	//std::vector<char>str_load;

	// 背景
	D3DXVECTOR2 m_pos;                      // 背景遷移判定上
	D3DXVECTOR2 m_move_pos;                 // 移動ベクトル
	int max_graph_num;
	int m_current_pos;                      // 今いる位置
	int m_connect1_graph;                   // 連結画像1 
	int m_connect2_graph;                   // 連結画像2
	int m_graph_difference;                 // 背景の端数

	// 遷移位置
	Map *m_pmap;
};