﻿#include"BackGround.h"
#include<stdlib.h>
#include"../../Lib/D3D9/D3D9.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"



BackGround::BackGround(
	const std::string&file_name,
	Map * map,
	SortObjectType sort_num,
	float graph_scale_x,
	float graph_scale_y) : 
	m_max_graph_num(0),
	m_move(0.f,0.f)
{

	// ソートオブジェクトの型を代入
	m_sort_object_type = sort_num;		                

	// 画像の縦端数を割り出し
	m_height_graph_difference = (int)(Window::HEIGHT - graph_scale_y) / 2;

	// 画像の横端数を割り出し
	m_width_graph_difference = (int)(Window::WIDTH - graph_scale_x) / 2;

	// 1画像は0番目から始める
	m_connect1_graph = 0;	

	// 2画像は1番目から始める
	m_connect2_graph = 1;			                     

	// 画像から縦の画面分の端数を割り出す
	m_height_graph_size_differance = graph_scale_y - Window::HEIGHT;

	// 最初の背景の位置x
	m_pos.x = (Window::WIDTH - graph_scale_x) / 2;	

	// 最初の背景の位置y
	m_pos.y = ((Window::HEIGHT + m_height_graph_size_differance) - graph_scale_y) / 2;		

	// 遷移スクロール位置のポインタを入れる。
	m_p_map = map;

	// ファイルの読み込み
	BGLoad(file_name.c_str());	
}


void BackGround::Update() {

	const int SCROLL_SPEED = 3;

	// 移動代入
	MoveSub();

	// マップスクロールの3分の１の速度にする
	MoveAdjustment(SCROLL_SPEED);

	// スクロールしてもいいなら
	if (IsScroll() == true) {

		// 位置Yに移動を加算
		PosYToMoveYAdd();

		// スクロール
		Scroll();
	}
}


void BackGround::Draw(){

	// m_graph_differenceで端数分横の位置をずらして描画している

	// 1枚目描画
	Texture::Draw2D(
		// 描画ファイル名
		m_p_bg_file_name_list[m_connect1_graph % m_max_graph_num],
		// 横のサイズ
		(float)m_width_graph_difference,
		// 縦のサイズ
		(m_pos.y + (float)((-Window::HEIGHT - m_height_graph_size_differance) * m_connect1_graph) + (float)m_height_graph_difference)
	);
		
	// 2枚目描画
	Texture::Draw2D(
		// 描画ファイル名
		m_p_bg_file_name_list[m_connect2_graph % m_max_graph_num],
		// 横のサイズ
		(float)m_width_graph_difference,
		// 縦のサイズ
		(m_pos.y + (float)((-Window::HEIGHT - m_height_graph_size_differance) * m_connect2_graph) + (float)m_height_graph_difference)// +10.f
	);
}


// 背景スクロール
void BackGround::Scroll() {

	// 画面遷移基準
	const int GRAPH_SIZE_H = static_cast<int>(Window::HEIGHT + m_height_graph_size_differance);
	
	// 描画切り替え領域上
	const int CHANGE_GRAPH_POS_UP = static_cast<int>(m_pos.y - BG_CHANGE_LINE);

	// 上にスクロールしている場合の描画切り替え
	{
		// 連結1画像が描画軸になっており、描画軸が進んだ時、連結2画像を1シート先に描画させるようにする
		if ((CHANGE_GRAPH_POS_UP) >= (GRAPH_SIZE_H * m_connect1_graph)) {
			m_connect2_graph = m_connect1_graph + 1;
		}

		// 連結2画像が描画軸になっており、描画軸が進んだ時、連結1画像を1シート先に描画させるようにする
		if ((CHANGE_GRAPH_POS_UP) >= (GRAPH_SIZE_H * m_connect2_graph)) {
			m_connect1_graph = m_connect2_graph + 1;
		}
	}
	
	// 描画切り替え領域下
	const int CHANGE_GRAPH_POS_DOWN = static_cast<int>(m_pos.y + GRAPH_SIZE_H - GRAPH_DIFFERENCE + BG_CHANGE_LINE);

	// 下にスクロールしている場合の描画切り替え
	{
		// 連結1画像が描画軸になっており、描画軸が後退した時、次は連結2画像を1シート戻して描画させるようにする
		if ((CHANGE_GRAPH_POS_DOWN) <= ((GRAPH_SIZE_H) * (m_connect1_graph))) {
			m_connect2_graph = m_connect1_graph - 1;
		}

		// 連結2画像が描画軸になっており、描画軸が後退した時、次は連結1画像を1シート戻して描画させるようにする
		if ((CHANGE_GRAPH_POS_DOWN) <= (GRAPH_SIZE_H) * (m_connect2_graph + 1)) {
			m_connect1_graph = m_connect2_graph - 1;
		}
	}

	// 配列外アクセス禁止
	if (m_connect1_graph < 0 || m_connect2_graph < 0 || -m_pos.y >= 0) {

		m_connect1_graph = 0;
		m_connect2_graph = 1;
	}
}


bool BackGround::IsScroll(){

	// スクロール制限する
	bool is_scroll = true;

	// 上
	if (-m_p_map->GetPos() >= MAX_UP_SCROLL) {
		is_scroll = false;
	}

	// 下
	else if (-m_p_map->GetPos() < 0.f) {
		is_scroll = false;
	}

	// スクロール制限するかどうかを返す
	return is_scroll;
}


void BackGround::BGLoad(const char*file_name) {

	// 文字列バッファサイズ
	const int STRING_BUFFER = 256;

	// ストリーム
	FILE*fp;
	// ファイルオープン
	fopen_s(&fp, file_name, "r");

	// 文字列バッファ
	char str_load_buf[1000][100] = {};

	// ファイルが読み込まれてない場合
	if (fp == NULL) {
		return;
	}

	// 現在の数
	int current_num = 0;

	// 文字列読み込み、改行まで
	while (fgets(str_load_buf[current_num], STRING_BUFFER, fp) != NULL) {

		// 末尾にある改行文字列を削除
		if (str_load_buf[current_num][strlen(str_load_buf[current_num]) - 1] == '\n') {
			str_load_buf[current_num][strlen(str_load_buf[current_num]) - 1] = NULL;
		}

		// 文字列を読み込み
		m_p_bg_file_name_list.push_back(str_load_buf[current_num]);

		// 次の文字列へ
		current_num++;

		// 画像数加算
		m_max_graph_num++;
	}

	// ファイルを閉じる
	fclose(fp);
	return;
}


void BackGround::PosYToMoveYAdd() {
	// 上下だけ加算
	m_pos.y += m_move.y;
}

void BackGround::MoveSub() {

	m_move.y = m_p_map->GetMove();// 反対方向に行くので-変換
}

void BackGround::MoveAdjustment(int adjustment_num) {
	m_move.y /= adjustment_num;
}

float BackGround::GetMaxMapPos()const {
	// 背景サイズを一つ足す
	return (((Map::CHIP_SIZE * 18) + Window::HEIGHT) * m_max_graph_num);
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