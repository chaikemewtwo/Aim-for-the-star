#pragma once
#include"../../GameObject/Object/Object.h"

/*

Objectを変更するセッターを作るべき
誰の座標を使っているかを知る必要がある

*/

class MapChip; //マップの前方参照

// 背景クラス
class BackGround : public Object{
public:

	// constexprはコンパイル時定数になる
	static constexpr int GRAPH_NUM = 5;
	// 背景の大きさ
	static constexpr int GRAPH_SCALE_H = 1180;
	static constexpr int GRAPH_SCALE_W = 1920;
	// 背景の端数
	static constexpr int GRAPH_DIFFERENCE = 50;
	// 背景が入れ替わる範囲
	static constexpr float BG_CHANGE_LINE = 10.f;

	// ファイル名とスクロールする位置の参照をいれる。
	BackGround(const std::string&file_name,MapChip*map,SortObject sort_num);

	void Update();
	void Draw();

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

	// 背景文字列
	const char* m_pback_str[GRAPH_NUM];
	// 読み込み専用のもの
	char str_load[GRAPH_NUM][500];

	// 背景
	D3DXVECTOR2 m_pos;// 背景遷移判定上
	D3DXVECTOR2 m_move_pos;// 移動ベクトル

	// 今いる位置
	int m_now_pos;

	// 今の画像
	int m_now_graph;
	int m_next_graph;

	// 遷移位置
	MapChip *m_pmap;
};