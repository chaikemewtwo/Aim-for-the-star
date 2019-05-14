#include"D3D9.h"
#include"../Lib/Window/Window.h"
#include"../Lib/Texture/Texture.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Input/KeyBord.h"
#include"../Map/MapTip.h"
#include"../Enemy/Enemy/EnemyManager.h"
#include"../Player/Player.h"


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
MapTip::MapTip(Player*star1,Player*star2,EnemyManager*e_mng) {

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

	for (int i = 0; i < PLAYER_NUM; i++) {
		m_move_pos[i].x = m_move_pos[i].y = 0.f;
		m_obj_pos[i].x = m_obj_pos[i].y = 0.f;
	}

	// HACK 同じ処理を一つにまとめなければならない
	// 自機1の当たり判定処理

	
	for (int i = 0; i < PLAYER_NUM; i++) {// 一旦当たり判定を一つにする

		// マップチップの位置変更
		m_obj_pos[i].x = m_pbase[i]->GetPos().x;
		m_obj_pos[i].y = m_pbase[i]->GetPos().y;

		// 移動位置変更
		m_move_pos[i] = m_pbase[i]->GetMovePos();

		// 当たり判定
		MapColider(i);

		// スクロールライン
		DrawLineIsActive(m_obj_pos[i].y, m_move_pos[i].y,m_scroll_range_up,m_scroll_range_down);

		// 自機(obj)の位置変更
		m_pbase[i]->SetPos(m_obj_pos[i]);
		// 自機の移動ベクトル変更
		m_pbase[i]->SetMovePos(m_move_pos[i]);

	}

	// マップ関連
	{
		// マップ座標にマップの移動ベクトルを加算
		m_map_pos.y += m_map_move_pos.y;
		// 初期化
		m_map_move_pos.x = m_map_move_pos.y = 0.f;
		// 着地点
		LandOnTheGround();
	}
}


// マップの描画
void MapTip::Draw() {


	// 前進するごとにチップを置き換える
	// TODO いずれはどちらの自機が優先されるか決める。

	// MEMO
	// マップ座標とスクリーン座標を作るべき

	// HACK 2回描画を行っているのは、描画がズレてないか確認するため
		// どこから描画するか
		int draw_range_begin = GetChipPosCast(-m_map_pos.y);// 描画のし始め // 前10
		int draw_range_end = GetChipPosCast(-m_map_pos.y) + MAP_NUM_Y + 20;// 描画の終わり// 前10

		// MEMO マップチップ番号の敵が生成されている場合は生成しない感じにしたらいい

		for (int y = draw_range_begin; y < draw_range_end; y++) {
			for (int x = 0; x < MAP_NUM_X; x++) {

				// 配列外アクセスは許させない
				if ((m_height_map_num)-y + MAP_NUM_Y < 0 || x < 0) {
					return;
				}

				if (m_draw_map[(m_height_map_num) - y + MAP_NUM_Y][x] == 1) {

					Texture::Draw2D("Resource/Texture/Map/chip_map_image_64.png",
						(float)(x * CHIP_SIZE),
						(float)(-y * CHIP_SIZE) + 2200 - m_map_pos.y);// 前 1647
				}
			}
		}
	
}



// 遷移はy軸だけ
int MapTip::DrawLineIsActive(float&pos_y, float&move_y, float up_range, float down_range) {

	// 描画遷移範囲 = 現在のマップ座標(本来はスクリーン座標の方がいい) + 遷移範囲(スクリーンから見て)

	// 上の遷移基準
	if (pos_y < up_range) {// (pos_y + (m_map_pos.y - INIT_MAP_POS_Y) < up_range + (m_map_pos.y - INIT_MAP_POS_Y))
		// スクリーン座標を戻す
		pos_y = up_range;// 移動分減算
		m_map_move_pos.y += move_y;// マップ座標を加算
		return 1;
	}
	// 下の遷移基準
	else if (pos_y > down_range) {// pos_y + (m_map_pos.y - INIT_MAP_POS_Y) > down_range + (m_map_pos.y - INIT_MAP_POS_Y
		
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

	int m_draw_range_begin = GetChipPosCast(m_obj_pos[0].y) + MAP_NUM_Y + 10;// 描画のし始め
	int m_draw_range_end = GetChipPosCast(m_obj_pos[0].y) + 10;// 描画の終わり

	for (int y = m_draw_range_end; y < m_draw_range_begin; y++) {
		for (int x = 0; x < MAP_NUM_X; x++) {

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

// 0番目がバグっている
void MapTip::MapColider(int i) {

	// 当たり判定
	Collision(m_obj_pos[i].x,m_obj_pos[i].y, &m_move_pos[i].x, &m_move_pos[i].y);
}


// 仮移動当たり判定
void MapTip::Collision(float &pos_x, float &pos_y, float *move_x, float *move_y) {

	// 修正定数
	const int RETOUCH = 1;

	// 当たり判定を左上からずらす
	D3DXVECTOR2 hit_point(0.f,0.f);

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
	if (GetChipParam(after_pos.x + hsize + hit_point.x,after_pos.y + CHIP_SIZE + hit_point.y) == 1||
		GetChipParam(after_pos.x + CHIP_SIZE - hsize + hit_point.x,after_pos.y + CHIP_SIZE + hit_point.y) == 1) {

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
	if (GetChipParam(after_pos.x + hsize + hit_point.x, after_pos.y + hit_point.y) == 1 ||
		GetChipParam(after_pos.x + CHIP_SIZE - hsize + hit_point.x, after_pos.y + hit_point.y) == 1) {
	
		// チップサイズ割り出し
		chip_pos_y = (float)GetChipPosCast(after_pos.y);
		//  チップサイズ = 現在の位置 + 一つ前のチップ
		pos_y = (chip_pos_y * CHIP_SIZE) + -((m_map_pos.y - INIT_MAP_POS_Y) - CHIP_SIZE);// -変換
		
		// スクロール範囲に入っていれば
		if (pos_y > m_scroll_range_down){
			m_map_pos.y += (pos_y - m_scroll_range_up);
		}
		// 移動ベクトルなし
		*move_y = 0.f;
	}

	// X軸左
	if (GetChipParam(after_pos.x + hit_point.x, after_pos.y + hsize + hit_point.y) == 1||
		GetChipParam(after_pos.x + hit_point.x, after_pos.y + CHIP_SIZE - hsize + hit_point.y) == 1) {// y軸も調べる

		chip_pos_x = static_cast<float>((int)(after_pos.x / CHIP_SIZE + RETOUCH));// 移動後が大きいので補正
		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE);
		// 移動ベクトルをなしにする
		*move_x = 0.f;
	}

	// X軸右
	if (GetChipParam(after_pos.x + CHIP_SIZE + hit_point.x, after_pos.y + hsize + hit_point.y) == 1 ||
		GetChipParam(after_pos.x + CHIP_SIZE + hit_point.x, after_pos.y + CHIP_SIZE - hsize + hit_point.y) == 1) {

		chip_pos_x = (float)GetChipPosCast(after_pos.x - CHIP_SIZE);
		//chip_pos_x = static_cast<float>((int)((after_pos.x - CHIP_SIZE) / CHIP_SIZE));
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
	int py = GetChipPosCast(pos_y);

	m_py = GetChipPosCast(pos_y);

	// 範囲外なら0
	if (px < 0 || px >= MAP_NUM_X || m_height_map_num + 1 - (m_py - MAP_NUM_Y) < 0) {
		return 0;
	}

	
	// マップの当たり判定をm_draw_mapに変更
	return m_draw_map[(m_height_map_num + 1) + (m_py - MAP_NUM_Y)][px];// 前 (py)
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
void MapTip::SetMovePos(D3DXVECTOR2&pos, int player_number) {
	m_move_pos[player_number] = pos;
}
void MapTip::SetPos(D3DXVECTOR2&pos, int player_number) {
	m_obj_pos[player_number] = pos;
}
D3DXVECTOR2 MapTip::GetPos(int player_number) {
	return m_obj_pos[player_number];
}
D3DXVECTOR2 MapTip::GetMovePos(int player_number) {
	return m_move_pos[player_number];
}