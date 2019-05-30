#include"BackGround.h"
#include<stdlib.h>
#include"../MapChip/MapChip.h"
#include"../../Lib/D3D/D3D9.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"



BackGround::BackGround(
	const std::string&file_name,
	Map*map,
	SortObject sort_num,
	float graph_scale_x,
	float graph_scale_y,
	bool scroll_limit) {


	m_sort_object = sort_num;		                 // ソート番号代入
	m_pos.x = m_pos.y = 0.f;		                 // 位置初期化
	m_max_graph_num = 0;				             // 画像数初期化
	m_h_difference = 
		(int)(WINDOW_H_F - graph_scale_y) / 2;       // 画像の縦端数初期化
	m_w_difference =
		(int)(WINDOW_W_F - graph_scale_x) / 2;       // 画像の横端数初期化
	m_current_pos = 0;				                 // 画像の現在位置初期化
	m_connect1_graph = 0;			                 // 連結画像1初期化
	m_connect2_graph = 1;			                 // 連結画像2初期化

	m_h_graph_difference = graph_scale_y - WINDOW_H_F;

	// 端数から中心位置に画像を配置できるようにする
	m_pos.x = (WINDOW_W_F - graph_scale_x) / 2;		 // 最初の背景の位置x
	m_pos.y = ((WINDOW_H_F + m_h_graph_difference) - graph_scale_y) / 2;		 // 最初の背景の位置y

	m_move.x = m_move.y = 0.f;		                 // 自機の移動初期化
	m_is_max_scroll = false;                           // スクロール最大
	m_is_scroll_limit = scroll_limit;

	// 遷移スクロール位置のポインタを入れる。
	m_pmap = map;
	// ファイルの読み込み
	BGLoad(file_name);	
}


void BackGround::Update() {

	MoveAdd();
	PosAdd();
	Scroll();
}


void BackGround::Draw(){

	/* 注意! UVをロードEx関数でずらしている */

	// m_graph_differenceで端数分横の位置をずらして描画している

	// 1枚目描画
		Texture::Draw2D(m_pback_str[m_connect1_graph % m_max_graph_num],
			(float)m_w_difference,
			(m_pos.y + (float)((-WINDOW_H_F - m_h_graph_difference) * m_connect1_graph) + (float)m_h_difference)
		);
		
	// 2枚目描画
		Texture::Draw2D(m_pback_str[m_connect2_graph % m_max_graph_num],
			(float)m_w_difference,
			(m_pos.y + (float)((-WINDOW_H_F - m_h_graph_difference) * m_connect2_graph) + (float)m_h_difference)// +10.f
		);
}


void BackGround::BGLoad(const std::string&file_name) {

	/* fgets行の終端の改行文字まで読み込み */

	FILE*fp; // ストリーム
	// ファイルオープン
	fopen_s(&fp,file_name.c_str(), "r");

	// ファイルが読み込まれてない場合
	if (fp == NULL) {
		return;
	}

	// 縦 
	int h = 0;

	// 文字列読み込み、改行まで
	while (fgets(str_load_buf[h], 256, fp) != NULL) {

		if (str_load_buf[h][strlen(str_load_buf[h]) - 1] == '\n'){
			str_load_buf[h][strlen(str_load_buf[h]) - 1] = NULL;
		}

		// 文字列読み込み
		m_pback_str.push_back(str_load_buf[h]);
			
		// 次の文字列へ
		h++;

		// 画像数加算
		m_max_graph_num++;
	}

	// ファイルを閉じる
	fclose(fp);
	return;
}


// 背景スクロール
void BackGround::Scroll() {


	// 画面遷移基準
	const int GRAPH_SIZE_H =      static_cast<int>(WINDOW_H_INT + m_h_graph_difference);
	const int CHANGE_RANGE_UP =   static_cast<int>(-m_pos.y - BG_CHANGE_LINE);
	const int CHANGE_RANGE_DOWN = static_cast<int>(-m_pos.y + GRAPH_SIZE_H - GRAPH_DIFFERENCE + BG_CHANGE_LINE);

	// 前にずれているか後ろにずれているかを判断して画像をずらす

	//if (m_connect1_graph == 3) {
	//	m_connect1_graph = 3;
	//}

	// MEMO 背景は-50 * -50を頂点に描画するので前は50piずらす必要はない
	// 前
	if ((CHANGE_RANGE_UP) <= (-GRAPH_SIZE_H * m_connect1_graph)) {
		m_connect2_graph = m_connect1_graph + 1;
	}

	// 前に進んでいる今
	if ((CHANGE_RANGE_UP) <= (-GRAPH_SIZE_H * m_connect2_graph)) {
		m_connect1_graph = m_connect2_graph + 1;
	}

	// 下に背景遷移ラインを貼る
	if ((CHANGE_RANGE_DOWN)>= ((-GRAPH_SIZE_H) * (m_connect1_graph - 1))) {

		m_connect2_graph = m_connect1_graph - 1;
	}

	// ラインより上の場合
	if ((CHANGE_RANGE_DOWN)>= (-GRAPH_SIZE_H) * (m_connect2_graph - 1)) {

		m_connect1_graph = m_connect2_graph - 1;
	}

	// デバッグエリア
	{

		// 最後の画像なら下まで行かせないようにする
		if (m_connect1_graph == 0 && -m_pos.y >= 0) {

			m_connect1_graph = 0;
			m_connect2_graph = 1;
		}
	}
}


bool BackGround::IsDownScrollLimit(){

	bool is_scroll = false;

	// 背景のスクロール制限
	// 上
	if (-m_pmap->GetPos().y > 0.f) {
		is_scroll = false;
	}
	// 下
	else if (-m_pmap->GetPos().y <= 0.f) {
		is_scroll = true;
	}

	// スクロール制限しない
	return is_scroll;
}


bool BackGround::IsUpScrollLimit() {

	bool is_scroll = false;

	// 最深部まで来たらスクロールを止める
	if ((float)((Map::CHIP_SIZE * 18) * m_max_graph_num - 1170) <= m_pos.y) {

		// 位置を戻す
		m_pmap->SetMapReset(-(((float)Map::CHIP_SIZE * 18) * m_max_graph_num - 1170) * m_max_graph_num);
		// スクロール領域を0にする
		m_pmap->SetScrollRangeUp(0.f);
		m_pos.y -= 1.f;

		m_is_max_scroll = true; // スクロール最大

		is_scroll = true;
	}
	else {
		// 元の状態に戻す
		is_scroll = false;
	}

	if ((float)((Map::CHIP_SIZE * 18) * m_max_graph_num - 900.f) <= m_pos.y) {
		m_pmap->SetScrollRangeUp(Map::SCROLL_RANGE_UP);
		m_pmap->SetIsScroll(true);
		is_scroll = false;
	}

	return is_scroll;
}


void BackGround::PosAdd() {

	bool is_limit = false;

	is_limit = IsUpScrollLimit();

	// 上下だけ加算
	if (IsDownScrollLimit() == false && is_limit == false) {
		m_pos.y += m_move.y;
	}
}


void BackGround::MoveAdd() {

	// プレイヤーの4分の１の速度にする
	m_move = m_pmap->GetMovePos() / 3;// 反対方向に行くので-変換
	
}


float BackGround::GetMaxMapPos()const{
	// 背景サイズを一つ足す
	return (((Map::CHIP_SIZE * 18.f) + 1180.f) * m_max_graph_num);
}


bool BackGround::IsMaxScroll()const{
	return m_is_max_scroll;
}


// 端数分GRAPH_DIFFERENCEでずらす

// UVをずらす処理を書く
//float uv_shift[2];

// 奇数か偶数で処理を変える
//if (m_connect1_graph % 1 || m_connect2_graph % 1) {
//	uv_shift[0] = -0.01f;
//}
//if (m_connect1_graph % 2 || m_connect2_graph % 2) {
//	uv_shift[1] = -0.01f;
//}
//else {
//	uv_shift[0] = 0.f;
//	uv_shift[1] = 0.f;
//}
//float shift_num[3];
//
//shift_num[0] = -0.01f;
//shift_num[1] = -0.01f;
//shift_num[2] = -0.01f;
//
//const char *str[3];
//
//str[0] = "Resource/Texture/Map/bg_hero_01.png";
//str[1] = "Resource/Texture/Map/bg_hero_02.png";
//str[2] = "Resource/Texture/Map/bg_hero_03.png";
//
//for (int i = 0; i < 3; i++) {
//
//	if (strcmp(m_pback_str[m_connect1_graph % max_graph_num], str[i]) == 0) {
//		uv_shift[0] = shift_num[i];
//	}
//	if (strcmp(m_pback_str[m_connect2_graph % max_graph_num], str[i]) == 0) {
//		uv_shift[1] = shift_num[i];
//	}
//
//}