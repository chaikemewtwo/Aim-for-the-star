#include"BackGround.h"
#include<stdlib.h>
#include"../../Lib/D3D9/D3D9.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"



BackGround::BackGround(
	const std::string&file_name,
	Map * map,
	SortObject sort_num,
	float graph_scale_x,
	float graph_scale_y) {


	m_sort_object_type = sort_num;		                 // ソート番号代入
	m_pos.x = m_pos.y = 0.f;		                     // 位置初期化
	m_max_graph_num = 0;				                 // 画像数初期化
	m_height_difference = 
		(int)(Window::HEIGHT - graph_scale_y) / 2;       // 画像の縦端数初期化
	m_width_difference =									 
		(int)(Window::WIDTH - graph_scale_x) / 2;        // 画像の横端数初期化
	m_current_pos = 0;				                     // 画像の現在位置初期化
	m_connect1_graph = 0;			                     // 連結画像1初期化
	m_connect2_graph = 1;			                     // 連結画像2初期化

	m_graph_height_size_differance = graph_scale_y - Window::HEIGHT;

	// 端数から中心位置に画像を配置できるようにする
	m_pos.x = (Window::WIDTH - graph_scale_x) / 2;		 // 最初の背景の位置x
	m_pos.y = ((Window::HEIGHT + m_graph_height_size_differance) - graph_scale_y) / 2;		 // 最初の背景の位置y

	m_move.x = m_move.y = 0.f;		                 // 自機の移動初期化

	// 遷移スクロール位置のポインタを入れる。
	m_pmap = map;
	// ファイルの読み込み
	BGLoad(file_name);	
}


void BackGround::Update() {

	// 移動代入
	MoveSub();
	// マップスクロールの3分の１の速度にする
	MoveAdjustment(3);

	// スクロールしてもいいなら
	if (IsScroll() == true) {
		// 位置Yに移動を加算
		PosYToMoveYAdd();
		// スクロール
		Scroll();
	}
}


void BackGround::Draw(){

	/* 注意! UVをロードEx関数でずらしている */

	// m_graph_differenceで端数分横の位置をずらして描画している

	// 1枚目描画
		Texture::Draw2D(m_pback_str[m_connect1_graph % m_max_graph_num],
			(float)m_width_difference,
			(m_pos.y + (float)((-Window::HEIGHT - m_graph_height_size_differance) * m_connect1_graph) + (float)m_height_difference)
		);
		
	// 2枚目描画
		Texture::Draw2D(m_pback_str[m_connect2_graph % m_max_graph_num],
			(float)m_width_difference,
			(m_pos.y + (float)((-Window::HEIGHT - m_graph_height_size_differance) * m_connect2_graph) + (float)m_height_difference)// +10.f
		);
}


void BackGround::BGLoad(const std::string&file_name) {

	/* fgets行の終端の改行文字まで読み込み */

	FILE*fp; // ストリーム
	// ファイルオープン
	fopen_s(&fp,file_name.c_str(), "r");

	char str_load_buf[10][100];
	//std::vector<std::string>string_load_buffer;
	std::string string_load_buffer;
	// ファイルが読み込まれてない場合
	if (fp == NULL) {
		return;
	}

	// 縦 
	int h = 0;

	// 要素確保
	string_load_buffer.reserve(h);
	// 数字確保
	string_load_buffer[h] = h;
	// 
	string_load_buffer.push_back.push_back(h);
	
	// 文字列読み込み、改行まで
	while (fgets(&string_load_buffer[h], 256, fp) != NULL) {// str_load_buf[h]

		//if(string_load_buffer[h][strlen(string_load_buffer.c_str())])
		if(str_load_buf[h][strlen(str_load_buf[h])])

		if (str_load_buf[h][strlen(str_load_buf[h]) - 1] == '\n'){
			str_load_buf[h][strlen(str_load_buf[h]) - 1] = NULL;
		}

		m_pback_str.push_back(str_load_buf[h]);

		// stringバージョン
		//if (string_load_buffer[h][strlen(string_load_buffer[h].c_str()) - 1] == '\n'){
		//	string_load_buffer[h][strlen(string_load_buffer[h].c_str()) - 1] = NULL;
		//}

		// 文字列読み込み
		//m_pback_str.push_back(string_load_buffer[h].c_str());
		
			
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
	const int GRAPH_SIZE_H =      static_cast<int>(Window::HEIGHT + m_graph_height_size_differance);
	const int CHANGE_RANGE_UP =   static_cast<int>(m_pos.y - BG_CHANGE_LINE);// -
	const int CHANGE_RANGE_DOWN = static_cast<int>(m_pos.y + GRAPH_SIZE_H - GRAPH_DIFFERENCE + BG_CHANGE_LINE);// -


	// 連結1画像が進んだ時、連結2画像を一つ先に描画させるようにする
	if ((CHANGE_RANGE_UP) >= (GRAPH_SIZE_H * m_connect1_graph)) {
		m_connect2_graph = m_connect1_graph + 1;
	}
	
	// 連結2画像が進んだ時、連結1画像を一つ先に描画させるようにする
	if ((CHANGE_RANGE_UP) >= (GRAPH_SIZE_H * m_connect2_graph)) {
		m_connect1_graph = m_connect2_graph + 1;
	}
	
	// 連結1画像が後退した時、次は連結2画像を後退して描画させるようにする
	if ((CHANGE_RANGE_DOWN)<= ((GRAPH_SIZE_H) * (m_connect1_graph - 1))) {
	
		m_connect2_graph = m_connect1_graph - 1;
	}
	
	// 連結画像2が後退した時、次は連結1画像を後退して描画させるようにする
	if ((CHANGE_RANGE_DOWN)<= (GRAPH_SIZE_H) * (m_connect2_graph - 1)) {
	
		m_connect1_graph = m_connect2_graph - 1;
	}

	// 配列外アクセスを起こさせないようにする
	if (m_connect1_graph == 0 && -m_pos.y >= 0) {

		m_connect1_graph = 0;
		m_connect2_graph = 1;
	}
}


bool BackGround::IsScroll(){

	bool is_scroll = true;

	// 背景のスクロール制限
	// 上
	if (-m_pmap->GetPos().y >= MAX_UP_SCROLL) {
		is_scroll = false;
	}
	// 下
	else if (-m_pmap->GetPos().y <= 0.f) {
		is_scroll = false;
	}

	// スクロール制限しない
	return is_scroll;
}


void BackGround::PosYToMoveYAdd() {
	// 上下だけ加算
	m_pos.y += m_move.y;
}

void BackGround::MoveSub() {

	m_move = m_pmap->GetMove();// 反対方向に行くので-変換
}

void BackGround::MoveAdjustment(int adjustment_num) {
	m_move.y /= adjustment_num;
}

float BackGround::GetMaxMapPos()const {
	// 背景サイズを一つ足す
	return (((Map::CHIP_SIZE * 18.f) + 1180.f) * m_max_graph_num);
}



//if ((CHANGE_RANGE_UP) <= (-GRAPH_SIZE_H * m_connect1_graph)) {
//	m_connect2_graph = m_connect1_graph + 1;
//}
//
//// 前に進んでいる今
//if ((CHANGE_RANGE_UP) <= (-GRAPH_SIZE_H * m_connect2_graph)) {
//	m_connect1_graph = m_connect2_graph + 1;
//}
//
//// 下に背景遷移ラインを貼る
//if ((CHANGE_RANGE_DOWN) >= ((-GRAPH_SIZE_H) * (m_connect1_graph - 1))) {
//
//	m_connect2_graph = m_connect1_graph - 1;
//}
//
//// ラインより上の場合
//if ((CHANGE_RANGE_DOWN) >= (-GRAPH_SIZE_H) * (m_connect2_graph - 1)) {
//
//	m_connect1_graph = m_connect2_graph - 1;
//}

//bool BackGround::IsUpScrollLimit() {
//
//	bool is_scroll = false;
//
//	// 最深部まで来たらスクロールを止める
//	if ((float)((Map::CHIP_SIZE * 18) * m_max_graph_num - 1170) <= m_pos.y) {
//
//		// 位置を戻す
//		m_pmap->SetMapReset(-(((float)Map::CHIP_SIZE * 18) * m_max_graph_num - 1170) * m_max_graph_num);
//		// スクロール領域を0にする
//		m_pmap->SetScrollRangeUp(0.f);
//		m_pos.y -= 1.f;
//
//		m_is_max_scroll = true; // スクロール最大
//
//		is_scroll = true;
//	}
//	else {
//		// 元の状態に戻す
//		is_scroll = false;
//	}
//
//	if ((float)((Map::CHIP_SIZE * 18) * m_max_graph_num - 900.f) <= m_pos.y) {
//		m_pmap->SetScrollRangeUp(Map::SCROLL_RANGE_UP);
//		m_pmap->SetIsScroll(true);
//		is_scroll = false;
//	}
//
//	return is_scroll;
//}



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