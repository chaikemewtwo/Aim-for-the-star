#include"D3D9.h"
#include"../../Lib/Window/Window.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"
#include"../MapChip/MapChip.h"
#include"../../Player/Player.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include<stdio.h>
#include<string>


// バグの報告

// スクロールのバグ
// 上下ヒトデが行ったらバグった
// スクロールで下と上に強制的に言ったらバグった
// スクロールすると当たり判定の戻す位置がずれる。

// structでチップに情報を持たせた方がいい

// マップチップオブジェクト配置

// MEMO
// 64ピクセル /* 横30 縦16 *//* 1088*/
// 128ピクセル/* 横15 縦8 *//*1024*/


// 2枚の背景でいける
// 当たり判定はずらした分だけ戻ってもいい

// ChipInfo

// コンストラクタ
Map::Map(Player*star1,Player*star2,EnemyManager*e_mng) {

	// ソートオブジェクト代入
	m_sort_object = MAP;

	// 自機の参照受け取り
	m_pbase[0] = star1;
	m_pbase[1] = star2;
	// 敵の参照受け取り
	e_pmng = e_mng;

	// マップ座標初期化
	// m_pos = マップ座標として作る
	m_pos.x = INIT_MAP_POS_X;
	m_pos.y = INIT_MAP_POS_Y;// 画面上まで
	// マップ座標移動座標初期化
	m_move_pos.x = 0.f;
	m_move_pos.y = 0.f;
	
	// スクロールする範囲初期化
	m_scroll_range_up = SCROLL_RANGE_UP;
	m_scroll_range_down = SCROLL_RANGE_DOWN;

	// ファイル読み込み
	Load("Map/MapData/MapData.csv");

	// とりあえずべた書き
	chip_str[0] = "Resource/Texture/Map/chip-map_image_01.png";
	chip_str[1] = "Resource/Texture/Map/chip-map_image_02.png";
	chip_str[2] = "Resource/Texture/Map/chip-map_image_03.png";
	chip_str[3] = "Resource/Texture/Map/chip-map_image_04.png";
	chip_str[4] = "Resource/Texture/Map/chip-map_image_05.png";
	chip_str[5] = "Resource/Texture/Map/chip-map_image_06.png";
	chip_str[6] = "Resource/Texture/Map/chip-map_image_07.png";
	chip_str[7] = "Resource/Texture/Map/chip-map_image_08.png";
	chip_str[8] = "Resource/Texture/Map/chip-map_image_09.png";
	chip_str[9] = "Resource/Texture/Map/chip-map_image_10.png";

	// u縦
	// v横
	// UVずらし配列初期化
	for (int i = 0; i < 10; i++) {
		chip_u[i] = 0.f;
		chip_v[i] = 0.f;
	}

	chip_u[0] = 0.01f;
	chip_v[1] = -0.001f;
	chip_v[6] = -0.01f;
	chip_v[5] = -0.01f;
	chip_v[8] = -0.001f;
	chip_v[3] = -0.001f;
	chip_v[7] = -0.01f;
	chip_v[9] = -0.01f;
	
	chip_u[8] = -0.01f;
	chip_u[7] = -0.01f;
	chip_u[9] = -0.01f;
	
	bedrock_chip[0].x = 2.f; bedrock_chip[0].y = 0.f;
	bedrock_chip[1].x = 2.f; bedrock_chip[1].y = 1.f;
	bedrock_chip[2].x = 1.f; bedrock_chip[2].y = 0.f;
	bedrock_chip[3].x = 0.f; bedrock_chip[3].y = 1.f;
	bedrock_chip[4].x = 0.f; bedrock_chip[4].y = 0.f;
	bedrock_chip[5].x = 2.f; bedrock_chip[5].y = -1.f;
	bedrock_chip[6].x = 0.f; bedrock_chip[6].y = -1.f;
	bedrock_chip[7].x = 0.f; bedrock_chip[7].y = 0.f;
	bedrock_chip[8].x = -1.f; bedrock_chip[8].y = 1.f;
	bedrock_chip[9].x = -1.f; bedrock_chip[9].y = -1.f;
	
	// 初期化集
	m_chip_num = 0;
	// ジャンプしているか
	m_is_stand = false;
	// 壁の衝突
	m_is_wall_col = false;
	// 壁の横衝突
	m_is_wall_col_side = false;
	// 壁の縦衝突
	m_is_wall_col_vertical = false;
	// スクロールしているか
	m_is_scroll = true;

	// 初期化時回りのオブジェクトを生成させる
	{
		int create_begin = GetChipCastByPos(-m_pos.y);
		int create_end = GetChipCastByPos(-m_pos.y) + (MAX_CHIP_NUM_H + 1);

		for (int y = create_begin; y < create_end; y++) {
			for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

				// 配列外アクセスは許させない
				if ((m_height_map_num) - y < 0 || x < 0) {
					return;
				}

				// 敵生成集め
				EnemyCreateGather(x, y, m_map[m_height_map_num - y][x].m_chip_num);
			}
		}
	}
}

void Map::Load(const std::string&file_name) {

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
			m_map[h][w++].m_chip_num = strtol(str2,&str2,10);// str2に変換できない文字列を入れる。

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


void Map::Update() {

	// オブジェクトの生成
	ObjectCreate();

	// マップの移動ベクトル初期化
	m_move_pos.x = m_move_pos.y = 0.f;

	for (int i = 0; i < 2; i++) {

		// 移動位置変更
		m_player_move_pos[i] = m_pbase[i]->GetMovePos();

		// 自機の位置を代入
		// 当たりポイントを補正
		m_player_pos[i].x = m_pbase[i]->GetPos().x + HIT_POINT_X;
		m_player_pos[i].y = m_pbase[i]->GetPos().y + HIT_POINT_Y;

		// 移動位置更新
		m_player_move_pos[i] = m_pbase[i]->GetMovePos();

	}

	// スクロールしてもいいかの判定
	//bool is_scroll = IsScrollLimit(m_player_pos[0].y, m_player_pos[1].y);

	for (int i = 0; i < 2; i++) {

		// スクロールしてもいいかどうか
		if (IsScroll() == true) {
			DrawLineIsActive(m_player_pos[i].y, m_player_move_pos[i].y, m_scroll_range_up, m_scroll_range_down);
		}
	}


	for (int i = 0; i < 2; i++) {// 一旦当たり判定を一つにする

		// 当たり判定
		MapCollision(m_player_pos[i],m_player_move_pos[i]);

		// 当たり位置を決める。
		m_player_pos[i].x -= HIT_POINT_X;
		m_player_pos[i].y -= HIT_POINT_Y;

		// 自機(obj)の位置変更
		m_pbase[i]->SetPos(m_player_pos[i]);
		// 自機の移動ベクトル変更
		m_pbase[i]->SetMovePos(m_player_move_pos[i]);
	}

	// マップ関連
	{
		// マップ座標にマップの移動ベクトルを加算
		m_pos.y += m_move_pos.y;
		
		// 着地点
		LandOnTheGround();
	}

	// オブジェクトの削除
	ObjectDestory();
}


// マップの描画
void Map::Draw() {

	// どこから描画するかを初期化
	int draw_range_begin = GetChipCastByPos(-m_pos.y);                      // 描画のし始め 
	int draw_range_end = GetChipCastByPos(-m_pos.y) + (MAX_CHIP_NUM_H + 1); // 描画の終わり

	// MEMO マップチップ番号の敵が生成されている場合は生成しない感じにしたらいい

	for (int y = draw_range_begin; y < draw_range_end; y++) {
		for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

			// 配列外アクセスは許させない
			if ((m_height_map_num)-y < 0 || x < 0) {
				return;
			}

			// ブロック描画範囲決定
			if (m_map[(m_height_map_num) - y][x].m_chip_num >= 1 && 
				m_map[(m_height_map_num)-y][x].m_chip_num <=MAX_BEDROCK_CHIP) {

				int current_num = m_map[(m_height_map_num)-y][x].m_chip_num - 1;

				Texture::Draw2DUVShift(chip_str[m_map[(m_height_map_num) - y][x].m_chip_num - 1],
					(float)(x * CHIP_SIZE) + bedrock_chip[current_num].x,
					(float)(-y * CHIP_SIZE) + 1080 - m_pos.y + bedrock_chip[current_num].y,
					chip_u[current_num],
					chip_v[current_num]);
			}
			// 0番目の文字列描画
			else if (m_map[(m_height_map_num) - y][x].m_chip_num == 1) {

				Texture::Draw2D(chip_str[m_map[0][x].m_chip_num],
					(float)(x * CHIP_SIZE),
					(float)(-y * CHIP_SIZE) + 1080 - m_pos.y);
			}

		}
	}

}


// 遷移はy軸だけ
int Map::DrawLineIsActive(float&pos_y, float&move_y, float up_range, float down_range) {

	// 描画遷移範囲 = 現在のマップ座標(本来はスクリーン座標の方がいい) + 遷移範囲(スクリーンから見て)

	// 上の遷移基準
	if (pos_y <= up_range) {
		// スクリーン座標を戻す
		pos_y = up_range;// 移動分減算
		// ここでバグが起こっている
		m_move_pos.y += move_y;// マップ座標を加算
		return 1;
	}

	// 下の遷移基準
	else if (pos_y >= down_range) {

		pos_y = down_range;

		m_move_pos.y += move_y;// マップ座標を加算
		return 2;
	}

	return 0;
}


// スクロールが上下行われているなら
bool Map::IsScrollLimit(float &pos_y1, float &pos_y2) {

	// 自機1が上、自機2が下の場合スクロール停止
	if (pos_y1 <= m_scroll_range_up + 60 && m_scroll_range_down <= pos_y2){
		// 位置を補正
		if (pos_y1 <= m_scroll_range_up){
			pos_y1 = m_scroll_range_up;
		}
		if (pos_y2 >= m_scroll_range_down){
			pos_y2 = m_scroll_range_down;
		}
 		return false;
	}

	// 自機1が下,自機2が上の場合スクロール停止
	else if (pos_y2 <= m_scroll_range_up + 60 && m_scroll_range_down <= pos_y1){

		if (pos_y2 <= m_scroll_range_up){
			pos_y2 = m_scroll_range_up;
		}
		if (pos_y1 >= m_scroll_range_down){
			pos_y1 = m_scroll_range_down;
		}
		return false;
	}

	return true;
}

// 注意!ここで色々初期化している
void Map::LandOnTheGround() {

	// 変更した
	// 着地点に着地したら
	if (m_pos.y >= INIT_MAP_POS_Y) {

		m_draw_range_down = 800.f;
		m_player_move_pos[0].y = 0.f;
		m_player_move_pos[1].y = 0.f;
		
		// マップの移動を初期化して移動させないようにする
		m_move_pos.y = 0.f;
		// マップ座標を初期化して移動させないようにする
		m_pos.y = 0.f;
	}
	else {
		m_draw_range_down = SCROLL_RANGE_DOWN;
	}
}



// 生成は上と下のラインを作り、作成する。
// それぞれ範囲外にでたら、アクティブをfalseにする。

void Map::ObjectCreate() {

	// 生成ライン
	int create_line[2];

	// 上
	create_line[0] = GetChipCastByPos(-m_pos.y) + CHIP_RANGE_UP;// 18
	// 下
	create_line[1] = GetChipCastByPos(-m_pos.y) + CHIP_RANGE_DOWN;// 1

	// 生成部分(下から生成していく)
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

			// 配列外アクセスは許させない
			if (m_height_map_num - create_line[y] < 0 || x < 0) {
				return;
			}

			// 練習用にチップ描画
			//if (m_map[m_height_map_num - create_line[y]][x].m_chip_num == 1) {
			//	Texture::Draw2D("Resource/Texture/Enemy/hora_ready.png",(float)(CHIP_SIZE * x),((float)(CHIP_SIZE * -create_line[y]) + 
			//		WINDOW_H_F - m_pos.y));
			//}

			// オブジェクト生成、チップ番号が51以上なら
			if (m_map[m_height_map_num - create_line[y]][x].m_chip_num >= 100) {

				// 位置を代入
 				D3DXVECTOR2 pos((float)(CHIP_SIZE * x), (CHIP_SIZE * -create_line[y]) + WINDOW_H_F - m_pos.y);// マップ座標加算

				// チップを消すタイミング、チップを生成するタイミングが必要
				// チップが活動していないなら
				if (m_map[m_height_map_num - create_line[y]][x].m_is_active == false){
					// 敵生成
					EnemyCreateGather(x, create_line[y], m_map[m_height_map_num - create_line[y]][x].m_chip_num);
					// マップチップ記録
					m_map[m_height_map_num - create_line[y]][x].m_is_active = true;
				}
			}
		}
	}
}


void Map::ObjectDestory() {

	// 削除ライン
	int destory_line[2];

	// 上
	destory_line[0] = GetChipCastByPos(-m_pos.y) + CHIP_RANGE_UP + 1;
	// 下
	destory_line[1] = GetChipCastByPos(-m_pos.y) + CHIP_RANGE_DOWN - 2;

	
	// 生成部分(下から生成していく)
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

			// 配列外アクセスは許させない
			if (m_height_map_num - destory_line[y] < 0 || x < 0) {
				return;
			}

			// チップが活動しているなら
			if (m_map[(m_height_map_num - destory_line[y])][x].m_is_active == true){
				// マップチップ活動中にする
				m_map[(m_height_map_num - destory_line[y])][x].m_is_active = false;
			}
		}
	}
}


void Map::MapCollision(D3DXVECTOR2&pos,D3DXVECTOR2&move) {

	// 当たり判定を取っているサイズ
	/* 
	縦128
	横64
	*/

	const float RS = 1.f; // ResizeのRS.サイズを補正
	int chip_num = 0;     // チップ番号を記録する用

	// 左上
	D3DXVECTOR2 up_left(pos.x + RS + SHRINK_X, pos.y + RS + SHRINK_Y);
	// 右上
	D3DXVECTOR2 up_right(pos.x + CHIP_SIZE - RS - SHRINK_X, pos.y + RS + SHRINK_Y);
	// 左下
	D3DXVECTOR2 down_left(pos.x + RS + SHRINK_X, pos.y + CHIP_SIZE - RS - SHRINK_Y);
	// 右下
	D3DXVECTOR2 down_right(pos.x + CHIP_SIZE - RS - SHRINK_X, pos.y + CHIP_SIZE - RS - SHRINK_Y);

	{
		// y軸の衝突判定(四隅)
		if ( m_is_stand = IsFloorCollision(up_left.x, up_left.y, 0.f, move.y,chip_num) == true ||// ジャンプフラグを受け取る
			IsFloorCollision(up_right.x, up_right.y, 0.f, move.y,chip_num) == true ||
			IsFloorCollision(down_left.x, down_left.y + CHIP_SIZE, 0.f, move.y,chip_num) == true ||// 衝突点を1CHIP下にずらしている
			IsFloorCollision(down_right.x, down_right.y + CHIP_SIZE, 0.f, move.y,chip_num) == true) {

			// 衝突している

			// 縦の衝突判定とアクション
			ChipAction(pos, move, chip_num,COL_Y);
			m_is_wall_col_vertical = true;
		}
		else {
			// 衝突していない
			m_is_wall_col = false;
			m_is_wall_col_vertical = false;
		}
	}

	// y軸更新
	up_left.y = pos.y + RS + SHRINK_Y;
	up_right.y = pos.y + RS + SHRINK_Y;
	down_left.y = pos.y + CHIP_SIZE - RS - SHRINK_Y;
	down_right.y = pos.y + CHIP_SIZE - RS - SHRINK_Y;

	{
		// x軸の衝突判定(四隅)

		if (IsFloorCollision(up_left.x, up_left.y, move.x, 0.f,chip_num) == true ||
			IsFloorCollision(up_right.x, up_right.y, move.x, 0.f,chip_num) == true ||
			IsFloorCollision(down_left.x, down_left.y + CHIP_SIZE, move.x, 0.f,chip_num) == true ||// 衝突点を1CHIP下にずらしている
			IsFloorCollision(down_right.x, down_right.y + CHIP_SIZE, move.x, 0.f,chip_num) == true) {

			// 横の衝突判定
			ChipAction(pos, move, chip_num,COL_X);
			m_is_wall_col_side = true;
		}
		// x軸の中心衝突判定
		else if (IsFloorCollision(down_left.x, down_right.y, move.x, 0.f,chip_num) == true ||// 左下
			IsFloorCollision(down_right.x, down_right.y, move.x, 0.f,chip_num) == true) {  // 右下

			// 横の衝突判定
			ChipAction(pos, move, chip_num,COL_X);
			m_is_wall_col_side = true;
		}
		else {
			// 衝突していない
			m_is_wall_col = false;
			m_is_wall_col_side = false;
		}
	}
}


// これでできない場合は定数にする
void Map::ChipAction(D3DXVECTOR2 &pos, D3DXVECTOR2&move_pos,int chip_num, COL_DIRECTION col_d) {

	// 吸いつきブロック
	if (chip_num == 12) {
		StuckCenterChip(pos.x, pos.y, move_pos.x, move_pos.y);
	}
	// 衝突ブロックなら
	else if (col_d == COL_Y) {

		NowPosYFixToMapPos(pos.y, move_pos.y);
		m_is_wall_col = true;
	}
	else if (col_d == COL_X) {
		NowPosXFixToMapPos(pos.x, move_pos.x);
		m_is_wall_col = true;
	}
}


bool Map::IsFloorCollision(float pos_x, float pos_y,float move_x,float move_y) {

	// 現在のスクリーン座標にマップ座標を加算する
	D3DXVECTOR2 after_pos(pos_x + move_x,pos_y + move_y + (m_pos.y) + m_move_pos.y);

	// 床と衝突しているか(障害物は50番号まで),0番号は何もなし
	if (GetChipParam(after_pos.x, after_pos.y) <= 50 && GetChipParam(after_pos.x, after_pos.y) >= 1) {

		// 衝突している
		return true;
	}
	
	// 衝突していない
	return false;
}

// オーバーロード
bool Map::IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y, int &col_chip) {

	if (IsFloorCollision(pos_x, pos_y, move_x, move_y) == true) {

		// チップを入れる
		col_chip = GetChipParam(pos_x + move_x, pos_y + move_y + m_pos.y + m_move_pos.y);

		return true;
	}
	return false;
}


// 横マップの位置に修正
void Map::NowPosXFixToMapPos(float &pos_x, float &move_x) {

	// 修正定数
	const int RETOUCH = 1;
	// 入ったマップチップの座標を割り出す
	float chip_pos_x = 0;

	// 左
	if (move_x < 0.f) {

		chip_pos_x = (float)GetChipCastByPos(pos_x - (move_x - RETOUCH));

		pos_x = (chip_pos_x * CHIP_SIZE);

		// 縮小する時
		if (SHRINK_Y > 0.f) {
			pos_x += (CHIP_SIZE - SHRINK_X);
		}

		// 移動ベクトルなし
		move_x = 0.f;
	}

	// 右
	else if (move_x > 0.f) {
		
 		chip_pos_x = (float)GetChipCastByPos(pos_x + move_x);
		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE) + SHRINK_X;

		// 移動ベクトルなし
		move_x = 0.f;
	}
}


void Map::NowPosYFixToMapPos(float &pos_y, float &move_y) {

	// 修正定数
	const int RETOUCH = 1;
	// 入ったマップチップの座標を割り出す
	float chip_pos_y = 0.f;

	// 上(自機の移動とマップの移動が進んだ時)
	if (move_y < 0.f || m_move_pos.y < 0.f) {

		// チップサイズ割り出し
		chip_pos_y = (float)GetChipCastByPos((pos_y +(m_pos.y)) - (move_y - RETOUCH + SHRINK_Y));// SHRINK_Y関係のバグ

		pos_y = (chip_pos_y * CHIP_SIZE) + (-m_pos.y) - m_move_pos.y;

		// 縮小する時
		if (SHRINK_Y > 0.f) {
			// 修正(自機の移動とマップの移動を加算)
			pos_y += (CHIP_SIZE - SHRINK_Y);
		}
		
		// スクロール範囲に入っていれば
		if (pos_y < m_scroll_range_up) {
			m_pos.y += (pos_y - m_scroll_range_up);
		}
	
		// 移動ベクトルなし
		move_y = 0.f;
	}

	// 下(自機の移動とマップの移動が進んだ時)
	else if (move_y > 0.f || m_move_pos.y > 0.f) {

		// チップサイズ割り出し
		chip_pos_y = (float)GetChipCastByPos((pos_y + m_pos.y) + move_y);

		pos_y = (chip_pos_y * CHIP_SIZE) + (-m_pos.y);

		pos_y += -move_y - m_move_pos.y;

		if (SHRINK_Y > 0.f) {
			pos_y += SHRINK_Y;
		}

		// スクロール範囲に入っていれば
		if (pos_y > m_scroll_range_down) {
			m_pos.y += (pos_y + m_scroll_range_down);
		}

		// 移動ベクトルなし
		move_y = 0.f;
	}
}


// 引っ付き処理
void Map::StuckCenterChip(float &pos_x, float &pos_y, float &move_x, float &move_y) {

	// チップ位置を作る
	int chip_x_r = GetChipCastByPos(pos_x) + 1;
	int chip_x_l = GetChipCastByPos(pos_x);
	int chip_y_u = GetChipCastByPos(pos_y + m_pos.y);// 位置を補正
	int chip_y_d = GetChipCastByPos(pos_y + m_pos.y) + 1;
	
	float hsize = (float)CHIP_SIZE / 2;

	// 自機を中心位置にずらす処理を行う

	// 上
	if (move_y > 0.f) {
		
		pos_y = (chip_y_u * (float)(CHIP_SIZE)) + hsize - m_pos.y;
	}
	// 下
	else if (move_y < 0.f) {
		pos_y = (chip_y_d * (float)(CHIP_SIZE)) - hsize - m_pos.y;
	}
	
	// 右
	if (move_x > 0.f) {
		pos_x = (chip_x_r * (float)CHIP_SIZE) - hsize;
	}
	// 左
	else if (move_x < 0.f) {
		pos_x = (chip_x_l * (float)CHIP_SIZE) + hsize;
	}
}


// セルに変換
int Map::GetChipCastByPos(const float&pos)const{
	return static_cast<int>(std::floor(pos / CHIP_SIZE));
}


// 座標を入れたらマップチップの位置を返す
int Map::GetChipParam(const float &pos_x, const float&pos_y) {

	// マップ座標変換
	int px = GetChipCastByPos(pos_x);
	int py = GetChipCastByPos(pos_y);

	// マップチップ範囲外なら戻す
	if (px < 0 || px >= MAX_CHIP_NUM_W ||
		(m_height_map_num + 1) + (py - MAX_CHIP_NUM_H) < 0 || py > MAX_CHIP_NUM_H) {
		return 0;
	}
	
	// マップの当たり判定をm_draw_mapに変更
	return m_map[(m_height_map_num + 1) + (py - MAX_CHIP_NUM_H)][px].m_chip_num;// 前 (py)
}


// 所定位置にブロックを置く
float Map::GetChipPosCastByChip(const float &chip_pos, const float &chip_y)const{
	
	return (chip_pos * CHIP_SIZE);
}

// マップのリセット
void Map::MapResat(float map_y) {
	m_pos.y = map_y;
}

/* アクセサ */
D3DXVECTOR2 Map::GetMovePos()const {// 元はmap
	return -m_move_pos;
}

// 着地しているか
bool Map::IsStand()const {
	return m_is_stand;
}

// 壁衝突しているか
bool Map::IsWallCollision()const {
	return m_is_wall_col;
}

// 縦の壁に衝突しているか
bool Map::IsWallVerticalCollision()const {
	return m_is_wall_col_vertical;
}

// 横の壁に衝突しているか
bool Map::IsWallSideCollision()const {
	return m_is_wall_col_side;
}

// スクロールしているか
bool Map::IsScroll()const {
	return m_is_scroll;
}


void Map::EnemyCreateGather(int x, int y, int chip_num) {

	// ウニ生成
	if (chip_num == 100) {
		// 位置を代入
		D3DXVECTOR2 pos((float)(CHIP_SIZE * x), (CHIP_SIZE * -y) + 1080 - m_pos.y);
		// 敵生成
		e_pmng->EnemyCreate(pos, this, m_pbase[0], m_pbase[1], SEAURCHIN);
		// マップチップ記録
		m_map[m_height_map_num - y][x].m_is_active = true;
	}
	// 落ちていくウニ生成
	else if (chip_num == 101) {
		// 位置を代入
		D3DXVECTOR2 pos((float)(CHIP_SIZE * x), (CHIP_SIZE * -y) + 1080 - m_pos.y);
		// 敵生成
		e_pmng->EnemyCreate(pos, this, m_pbase[0], m_pbase[1], NO_MOVE_SEAURCHIN);
		// マップチップ記録
		m_map[m_height_map_num - y][x].m_is_active = true;
	}
	// 貝生成
	else if (chip_num == 102) {
		// 位置を代入
		D3DXVECTOR2 pos((float)(CHIP_SIZE * x) + CHIP_SIZE, (CHIP_SIZE * -y) + CHIP_SIZE + 1080 - m_pos.y);
		// 敵生成
		e_pmng->EnemyCreate(pos, this, m_pbase[0], m_pbase[1], SELLFISH);
		// マップチップ記録
		m_map[m_height_map_num - y][x].m_is_active = true;
	}
	// 右下に行くブラインド生成
	else if (chip_num == 103) {
		// 位置を代入
		D3DXVECTOR2 pos((float)(CHIP_SIZE * x) + CHIP_SIZE, (CHIP_SIZE * -y) + CHIP_SIZE + 1080 - m_pos.y);
		// ブラインド生成
		e_pmng->BlindCreate(pos, D3DXVECTOR2(-100, WINDOW_H_F));
		// マップチップ記録
		m_map[m_height_map_num - y][x].m_is_active = true;
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

// もっと当たり後の処理を細分化するべきか
// 移動位置を初期化しないと使えないものになる

// 何もない所は数字すらいれない方がいいかも