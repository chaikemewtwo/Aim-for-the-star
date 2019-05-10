﻿#include"D3D9.h"
#include"../Lib/Window/Window.h"
#include"../Lib/Texture/Texture.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Input/KeyBord.h"
#include"../Map/MapTip.h"
#include"../Enemy/Enemy/EnemyManager.h"
#include"../Player/Star1/Star1.h"
#include"../Player/Star2/Star2.h"
#include"../DebugFont/oxdebugfont.h"


// バグの報告

// スクロールのバグ
// 上下ヒトデが行ったらバグった

// スクロールで下と上に強制的に言ったらバグった

// チップをでかくする

// マップチップオブジェクト配置

// MEMO
// 64ピクセル /* 横30 縦16 *//* 1088*/
// 128ピクセル/* 横15 縦8 *//*1024*/

// MEMO
// 画像位置を決めるとき
// 1シート目の必要な場所
// 描画で必要な場所,
// シートのどこからfor分を回すか
// ワールド座標を設置して
// 疑似的に統合
// for分を回す位置を決める

// 2枚の背景でいける
// 当たり判定はずらした分だけ戻ってもいい



// コンストラクタ
MapTip::MapTip(Star1*star1,Star2*star2,EnemyManager*e_mng) {

	// 自機の参照受け取り
	m_pbase[0] = star1;
	m_pbase[1] = star2;
	// 敵の参照受け取り
	e_pmng = e_mng;

	// マップ座標初期化
	m_map_pos.x = INIT_MAP_POS_X;
	m_map_pos.y = INIT_MAP_POS_Y;// 画面上まで
	// マップ座標移動座標初期化
	m_map_move_pos.x = 0.f;
	m_map_move_pos.y = 0.f;
	// スクロールする範囲初期化
	m_scroll_range_up = SCROLL_RANGE_UP;
	m_scroll_range_down = SCROLL_RANGE_DOWN;

	// ファイル読み込み
	Load("Map/MapData/MapData.csv");

	// デバッグ初期化
	m_py = 0;
	m_chip_num = 0;
}


void MapTip::Load(const std::string&file_name) {

	// fgets行の終端の改行文字まで読み込み
	FILE*fp;                                  // ストリーム
	const char *fname = file_name.c_str();    // ファイル名
	char str_buf[256];                        // 文字列バッファ

	// ファイルオープン
	fopen_s(&fp, fname, "r");

	// ファイルが読み込まれてない場合
	if (fp == NULL) {
		return;
	}

	// 縦 
	int h = 0;
	// 横
	int w = 0;

	// 文字列読み込み、改行まで
	while (fgets(str_buf, 256, fp) != NULL) {

		// 最初が改行と空白なら戻す
		if (str_buf[0] == '\n' || str_buf[0] == '\0') {
			//h++;
			continue;
		}

		// 文字列をバッファにいれる
		char *str2 = str_buf;

		// 次の列へ
		while(*str2 != '\0'&& *str2 != '\n') {

			// 整数値変換
			m_draw_map[h][w++] = strtol(str2,&str2,10);// str2に変換できない文字列を入れる。

		   // 文字列加算
		   str2++;
		}

		w = 0;

		// 次の行へ
		h++;
	}
	// 高さを記録
	m_height_map_num = h;

	// ファイルを閉じる
	fclose(fp);
	return;

}


void MapTip::Update() {

	// 初期化
	m_map_move_pos.x = m_map_move_pos.y = 0.f;

	for (int i = 0; i < PLAYER_NUM; i++) {
		m_move_pos[i].x = m_move_pos[i].y = 0.f;
		m_obj_pos[i].x = m_obj_pos[i].y = 0.f;
	}

	// HACK 同じ処理を一つにまとめなければならない
	// 自機1の当たり判定処理

	
	for (int i = 0; i < PLAYER_NUM; i++) {// 一旦当たり判定を一つにする

		// マップチップの位置変更
		m_obj_pos[i].x = m_pbase[i]->GetPos().x + HIT_POINT_X;
		m_obj_pos[i].y = m_pbase[i]->GetPos().y + HIT_POINT_Y;

		// 移動位置変更
		m_move_pos[i] = m_pbase[i]->GetMovePos();

		// 当たり判定
		MapColider(i);

		// スクロールライン
		DrawLineIsActive(m_obj_pos[i].y, m_move_pos[i].y,m_scroll_range_up,m_scroll_range_down);

		m_obj_pos[i].x -= HIT_POINT_X;
		m_obj_pos[i].y -= HIT_POINT_Y;

		// 自機(obj)の位置変更
		m_pbase[i]->SetPos(m_obj_pos[i]);
		// 自機の移動ベクトル変更
		m_pbase[i]->SetMovePos(m_move_pos[i]);

	}

	// マップ関連
	{
		// マップ座標にマップの移動ベクトルを加算
		m_map_pos.y += m_map_move_pos.y;
		
		// 着地点
		LandOnTheGround();
	}
}

int timer = 0;
// マップの描画
void MapTip::Draw() {

	// どこから描画するか
	int draw_range_begin = GetChipPosCast(-m_map_pos.y);                      // 描画のし始め 
	int draw_range_end = GetChipPosCast(-m_map_pos.y) + (MAX_CHIP_NUM_H + 1); // 描画の終わり

	// MEMO マップチップ番号の敵が生成されている場合は生成しない感じにしたらいい

	for (int y = draw_range_begin; y < draw_range_end; y++) {
		for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

			// 配列外アクセスは許させない
			if ((m_height_map_num)-y < 0 || x < 0) {
				return;
			}

			if (m_draw_map[(m_height_map_num)-y][x] == 1) {

				Texture::Draw2D("Resource/chip_map_image_64.png",
					(float)(x * CHIP_SIZE),
					(float)(-y * CHIP_SIZE) + 1080 - m_map_pos.y);
			}
		}
	}

		OX::DebugFont::print(
			500,
			480,
			0x000ffff,
			"range_num => %d",
			draw_range_begin - draw_range_end
			);

		// お試し描画
		OX::DebugFont::print(
			500,
			500,
			0x000ffff,
			"current_chip => %d",
			(int)(m_height_map_num + 1) + (m_py - MAX_CHIP_NUM_H));

		OX::DebugFont::print(
			500,
			520,
			0x000ffff,
			"py => %d",
			m_py);

		OX::DebugFont::print(
			500,
			540,
			0x000ffff,
			"PLAYER_POS_Y => %f",
			m_obj_pos[0].y);

		OX::DebugFont::print(
			500,
			560,
			0x000ffff,
			"player_pos.y - m_map_pos.y  => %f",
			m_obj_pos[0].y - m_map_pos.y
		);

		OX::DebugFont::print(
			500,
			580,
			0x000ffff,
			"m_after_pos_y => %f",
			m_after_pos_y
		);

		OX::DebugFont::print(
			500,
			600,
			0x000ffff,
			"m_map_pos.y => %f",
			m_map_pos.y
		);
}



// 遷移はy軸だけ
int MapTip::DrawLineIsActive(float&pos_y, float&move_y, float up_range, float down_range) {

	// 描画遷移範囲 = 現在のマップ座標(本来はスクリーン座標の方がいい) + 遷移範囲(スクリーンから見て)

	// 上の遷移基準
	if (pos_y < up_range) {
		// スクリーン座標を戻すs
		pos_y = up_range;// 移動分減算
		// ここでバグが起こっている
		m_map_move_pos.y += move_y;// マップ座標を加算
		return 1;
	}
	// 下の遷移基準
	else if (pos_y > down_range) {
		
		pos_y = down_range;
		
		m_map_move_pos.y += move_y;// マップ座標を加算
		return 2;
	}

	// なにもない0を返す
	return 0;
}


void MapTip::LandOnTheGround() {

	// 着地点に着地したら
	if (m_map_pos.y > INIT_MAP_POS_Y) {

		m_map_pos.y = INIT_MAP_POS_Y;
		m_move_pos[0].y = 0.f;
		m_move_pos[1].y = 0.f;
	}
}


void MapTip::ObjectCreate() {

	int m_draw_range_begin = GetChipPosCast(m_obj_pos[0].y) + MAX_CHIP_NUM_H + 10;// 描画のし始め
	int m_draw_range_end = GetChipPosCast(m_obj_pos[0].y) + 10;                   // 描画の終わり

	for (int y = m_draw_range_end; y < m_draw_range_begin; y++) {
		for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

			// 配列外アクセスは許させない
			if (m_height_map_num - y < 0 || x < 0) {
				return;
			}

			// オブジェクト生成、idの場所が0以上なら
			if (m_draw_map[m_height_map_num - y][x] >= 2) {

				// 位置を代入
				D3DXVECTOR2 pos((float)(x * CHIP_SIZE), (float)(-y * CHIP_SIZE) + 1674 + m_obj_pos[0].y);

				if (m_map_chip_id[m_height_map_num - y] == 0) {

					// 敵生成
					//e_pmng->Create(pos, m_pp);
					// マップチップ記録
					m_map_chip_id[m_height_map_num - y] = m_draw_map[m_height_map_num - y][x];

				}
			}
		}
	}
}


// 0番目がバグっている
void MapTip::MapColider(int i) {

	// 当たり判定
	Collision(m_obj_pos[i].x,m_obj_pos[i].y, &m_move_pos[i].x, &m_move_pos[i].y);
}


// 仮移動当たり判定
void MapTip::Collision(float &pos_x, float &pos_y, float *move_x, float *move_y) {

	// 修正定数
	const int RETOUCH = 1;

	// 現在のスクリーン座標にマップ座標を加算する
	D3DXVECTOR2 after_pos(pos_x + *move_x,
		pos_y + *move_y + (m_map_pos.y - INIT_MAP_POS_Y) + m_map_move_pos.y);
	// デバッグ変数
	m_after_pos_y = pos_y + *move_y + (m_map_pos.y - INIT_MAP_POS_Y);

	// 入ったマップチップの座標を割り出す
	float chip_pos_x = 0;
	float chip_pos_y = 0;

	// 現在、移動量増分のすり抜けが起こっている
	float hsize = CHIP_SIZE / 2;

	// Y軸床(ジャンプフラグを作る)
	if (GetChipParam(after_pos.x + hsize,after_pos.y) == 1||
		GetChipParam(after_pos.x + CHIP_SIZE - hsize,after_pos.y) == 1) {

		// チップサイズ割り出し(マップ座標も合わせて描画してあるので)
 		chip_pos_y = (float)GetChipPosCast(after_pos.y);
		//  現在の位置まで戻す = チップで当たった全体座標 + 全体マップでずらした分(最新マップ座標)
		pos_y = (chip_pos_y * CHIP_SIZE) + (-m_map_pos.y - INIT_MAP_POS_Y);
		
		// スクロール範囲に入っていれば
		if (pos_y < m_scroll_range_up) {
			m_map_pos.y += (pos_y - m_scroll_range_up);
		}
		// 移動ベクトルなし
		*move_y = 0.f;
	}

	// Y軸天井
	if (GetChipParam(after_pos.x + hsize, after_pos.y + CHIP_SIZE) == 1 ||// 上の当たり判定を広げる
		GetChipParam(after_pos.x + CHIP_SIZE - hsize, after_pos.y + CHIP_SIZE) == 1) {
	
		// チップサイズ割り出し
		chip_pos_y = (float)GetChipPosCast(after_pos.y);
		//  チップサイズ = 現在の位置 + 一つ前のチップ
		pos_y = (chip_pos_y * CHIP_SIZE) + -((m_map_pos.y - INIT_MAP_POS_Y) - CHIP_SIZE) + CHIP_SIZE;// -変換
		
		// スクロール範囲に入っていれば
		if (pos_y > m_scroll_range_down){
			m_map_pos.y += (pos_y - m_scroll_range_up);
		}
		// 移動ベクトルなし
		*move_y = 0.f;
	}

	// X軸左
	if (GetChipParam(after_pos.x, after_pos.y + hsize) == 1||
		GetChipParam(after_pos.x, after_pos.y + CHIP_SIZE - hsize) == 1) {// y軸も調べる

		chip_pos_x = (float)GetChipPosCast(after_pos.x) + RETOUCH;
		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE);
		// 移動ベクトルをなしにする
		*move_x = 0.f;
	}

	// X軸右
	if (GetChipParam(after_pos.x + CHIP_SIZE, after_pos.y + hsize) == 1 ||
		GetChipParam(after_pos.x + CHIP_SIZE, after_pos.y + CHIP_SIZE - hsize) == 1) {

		chip_pos_x = (float)GetChipPosCast(after_pos.x - CHIP_SIZE);
		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE) + CHIP_SIZE;
		// 移動ベクトルをなしにする
		*move_x = 0.f;
	}
}


// セルに変換
int MapTip::GetChipPosCast(const float&pos) {
	return static_cast<int>(std::floor(pos / CHIP_SIZE));
}


// 座標を入れたらマップチップの位置を返す
int MapTip::GetChipParam(const float &pos_x, const float&pos_y, const int&map_number) {

	// マップ座標変換
	int px = GetChipPosCast(pos_x);
	m_py = GetChipPosCast(pos_y);

	// 範囲外なら0
	if (px < 0 || px >= MAX_CHIP_NUM_W || (m_height_map_num + 1) + (m_py - MAX_CHIP_NUM_H) < 0) {
		return 0;
	}

	
	// マップの当たり判定をm_draw_mapに変更
	return m_draw_map[(m_height_map_num + 1) + (m_py - MAX_CHIP_NUM_H)][px];// 前 (py)
}

// 移動後の方向を返す
MapTip::Direction MapTip::GetMoveDirection(D3DXVECTOR2&move_pos) {

	// xマイナスの場合
	if (move_pos.x < 0.f) {
		return WEST;
	}
	// xプラスの場合
	else if (move_pos.x > 0.f) {
		return EAST;
	}
	// yマイナスの場合
	else if (move_pos.y < 0.f) {
		return NORTH;
	}
	// yプラスの場合
	else if (move_pos.y > 0.f) {
		return SOUTH;
	}

	return MAX;
}

// 所定位置にブロックを置く
void MapTip::SetPosParam(const int&pos_x, const int&pos_y, const int &cell, const int&map_number) {

	//map[map_number][pos_y][pos_x] = cell;
}

// マップのリセット
void MapResat() {

}

// アクセサ
D3DXVECTOR2 MapTip::GetMapPos()const{
	return m_map_pos;
}
D3DXVECTOR2 MapTip::GetMapMovePos()const {
	return m_map_move_pos;
}




// MEMO
/*
どのような地形に対して
どのように衝突したか
どこに戻るか
*/

// MEMO
/*
Y軸の4隅を調べ
X軸の4隅を調べる
*/

// あとマップの移動値を位置に足さないといけない
// マップ最大値まで来たらその分上がるようにする
// 原因はスクロール座標で逃げられないようになっている。→マップ座標をずらす。
