﻿#include"D3D9.h"
#include"./Lib/Window/Window.h"
#include"./Lib/Texture/Texture.h"
#include"./Lib/Texture/TextureBoad2D.h"
#include"./Lib/Input/KeyBord.h"
#include"../MapClass/Map/SeaMap.h"
//#include"oxdebugfont.h"



// 64ピクセル /* 横30 縦16 *//* 1088*/
// 128ピクセル/* 横15 縦8 *//*1024*/

// マップチップオブジェクト配置

// 画像位置を決めるとき
// 1シート目の必要な場所
// 描画で必要な場所,
// シートのどこからfor分を回すか
// ワールド座標を設置して
// 疑似的に統合
// for分を回す位置を決める

// 2枚の背景でいける
// 当たり判定はずらした分だけ戻ってもいい

int map[SeaMap::MAP_SAET_NUM][SeaMap::MAP_NUM_Y][SeaMap::MAP_NUM_X] = {
	{
		{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0, },
{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0, },
{ 1,1,1,0,0,0,0,0,0,0,0,0,1,1,1, },
{ 1,1,1,0,0,0,0,0,0,0,0,0,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
	},
{
	{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
},
{
	{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
},
{
	{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1, },
},
{
	{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,0,0,0, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1, },
},
};


// コンストラクタ
SeaMap::SeaMap() {

	m_player_pos.x = ((WINDOW_W_F / 2) - 200.f);
	m_player_pos.y = (-WINDOW_H_F / 2);// 高さは表示と逆の操作になるので、-変換 

	m_move_pos.x = m_move_pos.y = 0.f;

	m_chip_pos.x = m_chip_pos.y = 0.f;

	// 描画範囲を決める
	m_draw_range_begin = MAP_NUM_Y;
	m_draw_range_end = 0;

	// 動的生成
	//m_draw_map = new std::vector<std::vector<int>>;

	MapInit();
}

// 更新
void SeaMap::Update() {

	MapColider();
}


void SeaMap::MapInit() {

	int map_up = 0;

	for (int z = 0; z < MAP_SAET_NUM; z++) {

		// マップを上げる
		map_up = MAP_NUM_Y * z;

		for (int y = 0; y < MAP_NUM_Y; y++) {
			for (int x = 0; x < MAP_NUM_X; x++) {

				// at(y + map_up).at(x)
				// 参照にする予定,上から入れる。
				m_draw_map[y + map_up][x] = map[(MAP_SAET_NUM - 1) - z][y][x];
			}
		}
	}
}

// 描画
void SeaMap::Draw() {

	MapObjectCreateDraw();
}

// マップの描画
void SeaMap::MapObjectCreateDraw() {


	// 描画位置の開始地点
	D3DXVECTOR2 start_pos(0, 900);//y-50上の高さ


								  // 前進するごとにチップを置き換える
	m_draw_range_begin = GetChipPosCast(m_chip_pos.y) + MAP_NUM_Y;
	m_draw_range_end = GetChipPosCast(m_chip_pos.y);

	// 描画範囲を狭める
	for (int y = m_draw_range_end; y < m_draw_range_begin; y++) {
		for (int x = 0; x < MAP_NUM_X; x++) {

			// 配列外アクセスは許させない
			if (y < 0 || y>m_draw_range_begin) {
				y = 0;
			}

			// この配列描画
			if (m_draw_map[y][x] == 1) {

				Texture::Draw2D("Texture/renga.png", (float)(x * CHIP_SIZE) + start_pos.x,
					(float)(-y * CHIP_SIZE) + (INTERVAL_HEIGHT)+m_chip_pos.y + start_pos.y);
			}
		}
	}
}



/*
どのような地形に対して
どのように衝突したか
どこに戻るか
*/

void SeaMap::MapColider() {

	// 4隅調べる

	// 当たり判定
	Colision(m_player_pos.x, m_player_pos.y, &m_move_pos.x, &m_move_pos.y);

	// 加算
	m_player_pos += m_move_pos;

	// マップも移動
	m_chip_pos.y += m_move_pos.y;

	// 移動をなくす
	m_move_pos.x = m_move_pos.y = 0.f;

}


// 仮移動
void SeaMap::Colision(float &pos_x, float &pos_y, float *move_x, float *move_y) {

	// 修正定数
	const int RETOUCH = 1;

	// 移動後の座標を入れる
	float after_x = pos_x + *move_x;
	float after_y = pos_y + *move_y;

	// 入ったマップチップの座標を割り出す
	float chip_pos_x = 0;
	float chip_pos_y = 0;

	// それぞれ判定を行う

	/*
	Y軸の4隅を調べ
	X軸の4隅を調べる
	*/

	// 現在、移動量増分のすり抜けが起こっている
	float hsize = CHIP_SIZE / 2;


	// Y軸床(ジャンプフラグを作る)
	if (GetChipParam(after_x + hsize, -after_y + CHIP_SIZE, 4) == 1 ||
		GetChipParam(after_x + CHIP_SIZE - hsize, -after_y + CHIP_SIZE, 4) == 1) {

		// チップサイズ割り出し
		chip_pos_y = static_cast<float>((int)((-after_y) / CHIP_SIZE + 1));
		//  チップサイズ = 現在の位置 + 一つ前のチップ
		pos_y = (chip_pos_y * -CHIP_SIZE) + CHIP_SIZE;// これが原因

		*move_y = 0.f;
	}


	// Y軸天井
	else if (GetChipParam(after_x + hsize, -after_y, 4) == 1 ||
		GetChipParam(after_x + CHIP_SIZE - hsize, -after_y, 4) == 1) {

		// チップサイズ割り出し
		chip_pos_y = static_cast<float>((int)(-after_y / CHIP_SIZE));
		//  チップサイズ = 現在の位置 + 一つ前のチップ
		pos_y = (chip_pos_y * -CHIP_SIZE) - CHIP_SIZE;

		// 移動ベクトルなし
		*move_y = 0.f;
	}


	// X軸左
	if (GetChipParam(after_x, -after_y + hsize, 4) == 1 ||
		GetChipParam(after_x, -after_y + CHIP_SIZE - hsize, 4) == 1) {// y軸も調べる

		chip_pos_x = static_cast<float>((int)(after_x / CHIP_SIZE + 1));// 移動後が大きいので補正
																		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE_F);

		// 移動ベクトルをなしにする
		*move_x = 0.f;
	}

	// X軸右
	else if (GetChipParam(after_x + CHIP_SIZE, -after_y + hsize, 4) == 1 ||
		GetChipParam(after_x + CHIP_SIZE, -after_y + CHIP_SIZE - hsize, 4) == 1) {

		chip_pos_x = static_cast<float>((int)((after_x - CHIP_SIZE) / CHIP_SIZE));
		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE_F) + CHIP_SIZE;

		// 移動ベクトルをなしにする
		*move_x = 0.f;
	}


}



template<class T>
// セルに変換
int SeaMap::GetChipPosCast(const T&pos) {
	return static_cast<int>(std::floor(pos / CHIP_SIZE));
}

// 座標を入れたらマップチップの位置を返す
int SeaMap::GetChipParam(const float &pos_x, const float&pos_y, const int&map_number) {

	// マップ座標変換
	int px = GetChipPosCast(pos_x);
	int py = GetChipPosCast(pos_y);

	// 範囲外なら
	if (px < 0 || px >= MAP_NUM_X || py < 0 || py >= MAP_NUM_Y) {
		return 0;
	}

	return map[map_number][py][px];
}

// 所定位置にブロックを置く
void SeaMap::SetPosParam(const int&pos_x, const int&pos_y, const int &cell, const int&map_number) {

	map[map_number][pos_y][pos_x] = cell;
}


// マップのワープ
void MapWrap() {

}

// マップのリセット
void MapResat() {

}



