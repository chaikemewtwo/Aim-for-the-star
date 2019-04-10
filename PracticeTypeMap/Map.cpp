#include"D3D9.h"
#include"./Lib/Window/Window.h"
#include"./Lib/Texture/Texture.h"
#include"./Lib/Texture/TextureBoad2D.h"
#include"./Lib/Input/KeyBord.h"
#include"Map.h"
#include"oxdebugfont.h"



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

int map[Map::MAP_SAET_NUM][Map::MAP_NUM_Y][Map::MAP_NUM_X] = {
{
{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,},
{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,},
{ 1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,},
{ 1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
{ 1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,},
},
{
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
},
{
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
},
{
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,},
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
Map::Map() {

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
void Map::Update(){

	MapColider();
}


void Map::MapInit() {

	int map_up = 0;
	
	for (int z = 0; z < MAP_SAET_NUM; z++) {
	
		// マップを上げる
		map_up = MAP_NUM_Y * z;
	
		for (int y = 0; y < MAP_NUM_Y; y++) {
			for (int x = 0; x < MAP_NUM_X; x++) {
	
				// at(y + map_up).at(x)
				// 参照にする予定,上から入れる。
				m_draw_map[y + map_up][x] = map[(MAP_SAET_NUM - 1)- z][y][x];
			}
		}
	}
}

// 描画
void Map::Draw(){
	
	MapDraw();
}

// マップの描画
void Map::MapDraw() {

	
	// 描画位置の開始地点
	D3DXVECTOR2 start_pos(0,900);//y-50上の高さ


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
					
					Texture::Draw2D("renga.png", (float)(x * CHIP_SIZE) + start_pos.x,
						(float)(-y * CHIP_SIZE) + (INTERVAL_HEIGHT) + m_chip_pos.y + start_pos.y);	
				}
			}
		}
}



/*
どのような地形に対して
どのように衝突したか
どこに戻るか
*/

void Map::MapColider() {

	float Dummy = 0.f;

	int hsize = CHIP_SIZE / 2;

	
	// 当たり判定
	// 4隅調べる
	/*
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y + 1, &m_move_pos.x,&Dummy);
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y - 1, &m_move_pos.x,&Dummy);
	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y + 1, &m_move_pos.x, &Dummy);
	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y - 1, &m_move_pos.x, &Dummy);

	// ここで加算
	m_player_pos.x += m_move_pos.x;

	m_chip_pos.x += m_move_pos.x;

	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y - 1.f, &Dummy, &m_move_pos.y);
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y - 1.f, &Dummy, &m_move_pos.y);
	MapHitCheck(m_player_pos.x + 1.f, m_player_pos.y + 1.f, &Dummy, &m_move_pos.y);
	MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y + 1.f, &Dummy, &m_move_pos.y);
	

	// 加算
	m_player_pos.y += m_move_pos.y;

	m_chip_pos.y += m_move_pos.y;

	// 移動ベクトル初期化
	m_move_pos.x = m_move_pos.y = 0.f;
	*/

	
	Colision(m_player_pos.x, m_player_pos.y, &m_move_pos.x, &m_move_pos.y);

	// 加算
	m_player_pos += m_move_pos;

	// マップを上に上げる
	m_chip_pos.y += m_move_pos.y;

	m_move_pos.x = m_move_pos.y = 0.f;
	
}


// 細かい位置まで当たり判定を設定できる
void Map::MapHitCheck(float pos_x, float pos_y, float *move_x, float *move_y) {

	// 修正定数
	const int RETOUCH = 1;

	float after_x = pos_x + *move_x;
	float after_y = pos_y + *move_y;

	// 当たっていないなら
	if (GetChipParam(after_x, -after_y) != 1) {
		return;
	}

	// ここからは当たっている時の処理

	// 当たったセルを座標値に変換する


	// 上辺
	float up_pos = (float)((int)-after_y / CHIP_SIZE + RETOUCH) * CHIP_SIZE;
	// 下辺
	float down_pos = (float)((int)after_y / CHIP_SIZE) * CHIP_SIZE;
	// 左辺
	float left_pos = (float)((int)after_x / CHIP_SIZE + RETOUCH) * CHIP_SIZE;
	// 右辺
	float right_pos = (float)((int)after_x / CHIP_SIZE) * CHIP_SIZE;

	// 軸の仕組みを作る

	// 右辺に当たっていた場合
	if (*move_x > 0.f) {

		/* 移動量を補正する
		戻してほしい位置 - 現在地 = ブロック前までの移動量 */
		*move_x = right_pos - pos_x + 1.f;
		return;

	}
	// 左辺に当たっていた場合
	if (*move_x < 0.f) {

		*move_x = left_pos - pos_x - 1.f;
		return;
	}

	// 上辺に当たっていた場合
	if (*move_y > 0.f) {

		*move_y = up_pos + pos_y - 1.f;
		return;
	}

	// 下辺に当たっていた場合
	if (*move_y < 0.f) {

		*move_y = down_pos - pos_y + 1.f;
		return;
	}

}



// 仮移動
void Map::Colision(float &pos_x, float &pos_y, float *move_x, float *move_y) {

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

	if (*move_x >= 32.f) {
		*move_x = 32.f;
	}

	// Y軸床
	if (GetChipParam(after_x + hsize, -after_y + CHIP_SIZE) == 1 ||
		GetChipParam(after_x + CHIP_SIZE - hsize, -after_y + CHIP_SIZE)==1) {

		// チップサイズ割り出し
		chip_pos_y = (float)(int)(-after_y / CHIP_SIZE);
		//  チップサイズ = 現在の位置 + 一つ前のチップ
		pos_y = (-chip_pos_y * CHIP_SIZE) - CHIP_SIZE;// これが原因
	
		*move_y = 0.f;
	}

	
	// Y軸天井
	if (GetChipParam(after_x +hsize, -after_y,4) == 1 ||
		GetChipParam(after_x + CHIP_SIZE -hsize, -after_y,4) == 1) {

		// チップサイズ割り出し
		chip_pos_y = (float)(int)(-after_y / CHIP_SIZE);
		//  チップサイズ = 現在の位置 + 一つ前のチップ
		pos_y = (chip_pos_y * -CHIP_SIZE) - CHIP_SIZE;// これが原因

		// 移動ベクトルなし
		*move_y = 0.f;
	}


	// X軸左
	if (GetChipParam(after_x ,-after_y+hsize,4) == 1 ||
		GetChipParam(after_x, -after_y+ CHIP_SIZE+hsize,4)==1) {// y軸も調べる

		chip_pos_x = (float)((int)after_x / CHIP_SIZE + 1);// 移動後が大きいので補正
														   // 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE_F);

		// 移動ベクトルをなしにする
		*move_x = 0.f;
	}

	// X軸右
	if (GetChipParam(after_x + CHIP_SIZE, -after_y+hsize,4) == 1 ||
		GetChipParam(after_x + CHIP_SIZE, -after_y + CHIP_SIZE + hsize,4)==1) {

		chip_pos_x = (float)((int)(after_x - CHIP_SIZE) / CHIP_SIZE);
		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE_F) + CHIP_SIZE;

		// 移動ベクトルをなしにする
		*move_x = 0.f;
	}


	if (*move_x >= 32.f) {
		*move_x = 200;
	}

}



template<class T>
// セルに変換
int Map::GetChipPosCast(const T&pos) {
	return static_cast<int>(std::floor(pos/CHIP_SIZE));
}

// 座標を入れたらマップチップの位置を返す
int Map::GetChipParam(const float &pos_x,const float&pos_y,const int&map_number) {
	
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
void Map::SetChipParam(const int&pos_x,const int&pos_y,const int &cell, const int&map_number) {

	map[map_number][pos_y][pos_x] = cell;
}


// マップのワープ
void MapWrap() {

}

// マップのリセット
void MapResat() {

}







// 描画関係
//for (int i = 0; i < MAP_SAET_NUM; i++) {
//for (int y = 0; y < MAP_NUM_Y; y++) {
//	for (int x = 0; x< MAP_NUM_X; x++){
//
//		if (map[0][y][x] == 1) {
//
//			// ブロックよりも早く動かないといけない
//			// サイズ分に画像を変える
//			Texture::Draw2D("renga.png",(float)(x * CHIP_SIZE) + start_pos.x,
//				            (float)(y * CHIP_SIZE) + (INTERVAL_HEIGHT) + m_chip_pos.y);// チップの位置が自機の位置
//		}
//	}
//}
//}

/*
// 当たり判定遷移

int hsize = CELL_SIZE / 2;

// 左
// 実際に加算されていないので
// 移動ベクトルは実際に入れないと、移動していないことになるので無限に入る-1.fでも戻した値がそうなるので
if (GetCellParam( m_player_pos.x + speed.x, -m_player_pos.y, 0) == 1) {

// 戻す値を選択
int px = ((int)m_player_pos.x + (int)speed.x) / CELL_SIZE + 1;
px *= CELL_SIZE;

// 今の値と戻したい値を引いたら戻したい値までの移動値が出る
speed.x = px - (m_player_pos.x);
}

// 成功した例
//MapHitCheck(m_player_pos.x - 1.f, m_player_pos.y, &speed.x, &speed.y);

// 加算
m_player_pos += speed;

speed.x = speed.y = 0.f;
*/


// MEMO
// 4隅しらべる関数を作った方がいい
// 余計に関数にいれない為に、位置が更新されたらboolを使う

// 当たり判定

// 1セルの範囲で当たり判定を設定していたら、
// 1セル分飛ばして当たり判定を行ってしまう

// -の逆変換をどうにかしなければいけない

//// 上
//if (GetCellParam(m_player_pos.x,-m_player_pos.y + 10.f,0) == 1) {
//
//	m_player_pos.y = (float)m_player_pos.y + CELL_SIZE_F;
//}
//
//// 下
//if (GetCellParam(m_player_pos.x,-m_player_pos.y - 10.f,0) == 1) {
//
//	m_player_pos.y = (float)m_player_pos.y - CELL_SIZE_F;
//}
//
//// 右
//if (GetCellParam(m_player_pos.x + 10.f,-m_player_pos.y,0) == 1) {
//
//	m_player_pos.x = (float)m_player_pos.x - CELL_SIZE_F;
//}

// 移動量は後から代入する

// 384.0を目指す
// 16.f分移動している

//m_player_pos.x += 0.5f;// 当たり判定用


//if (-back_pos.y <= (-SCREEN_HEIGHT) * now_graph &&
//	FRACTION + (SCREEN_HEIGHT * now_graph) >= SCREEN_HEIGHT * now_graph) {
//
//	now_graph++;
//	next_graph = now_graph + 1;
//}


// 前描画
// 50 - 1180
//if (-back_pos.y <= (screen_up) * now_graph) {
//	next_graph = now_graph + 1;
//}
//
//if (-back_pos.y <= (screen_up + FRACTION) * (next_graph + 1)) {
//	now_graph = next_graph + 1;
//}

//Texture::Draw2D(str[4], 0.f, back_pos.y - (float)FRACTION + (-SCREEN_HEIGHT*0));

/*
// 画像が大きいのでこれぐらいになる
// 1枚目描画
Texture::Draw2D(str[4], 0.f,0.f + back_pos.y - (float)FRACTION);

// 最後でないなら
if (str[GRAPH_NUM] != str[4]) {

// 前描画
if (-back_pos.y <= -SCREEN_HEIGHT) {
// 2枚目描画
Texture::Draw2D(str[4], 0, (-SCREEN_HEIGHT - (float)FRACTION * 2) + back_pos.y);
}
else if (back_pos.y >= SCREEN_HEIGHT) {
// 2枚目描画
Texture::Draw2D(str[4], 0, (-SCREEN_HEIGHT - (float)FRACTION * 2) + back_pos.y);
}
}

// 画像更新(ここは関数でわけるべき)
// この描画更新は位置を戻し、背景だけ入れ替えるというもの

if (-back_pos.y <= -SCREEN_HEIGHT) {

p_pos.y = -FRACTION;
back_pos.y = -FRACTION;

now_graph++;
if (now_graph == 3) {
now_graph = 0;
}
}
else if (back_pos.y >= SCREEN_HEIGHT) {
p_pos.y = -FRACTION;
back_pos.y = -FRACTION;
}
*/



	/*
	const int GRAPH_NUM = 3;
	const int CHIP_SIZE = 32;

	const int CHIP_NUM_X = 20;
	const int CHIP_NUM_Y = 15;

	struct Graph {
		int player;     // 自機
		int background[GRAPH_NUM]; // 背景
		int chip[3];

		Graph() {
			player = 0;

			for (int i = 0; i < GRAPH_NUM; i++) {
				background[i] = 0;
			}
		}
	};

	void Init();
	void Draw();

	const int SCREEN_HEIGHT = 640;
	const int SCREEN_WIDTH = 480;


	int map[CHIP_NUM_Y][CHIP_NUM_X] = {

	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,2,2,2,2,2,2,2,1,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,2,2,2,2,2,2,2,1,0,0,0,0,0,1 },
	{ 1,0,0,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1 },
	{ 1,2,2,0,1,0,2,2,2,1,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,1,0,2,2,2,1,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,0,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,1,1,1,1,1,1,1,1,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,0,2,2,2,0,0,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,1,2,2,2,0,1,0,0,2,2,1 },
	{ 1,2,2,0,0,0,2,2,2,1,2,2,2,0,1,0,0,2,2,1 },
	{ 1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,2,2,1 },
	{ 1,0,0,0,0,1,2,2,2,2,2,2,2,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,1,2,2,2,2,2,2,2,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1 },
	};


	int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {


		// 初期化
		if (DirectXInit() == false) {
			return-1;
		}

		// ウィンドウサイズ
		//SetWindowSize(1020, 1080);

		// グローバル変数
		D3DXVECTOR2 p_pos;
		Graph gra;

		p_pos.x = p_pos.y = 0.f;
		p_pos.x = 3.f;
		p_pos.y = 3.f;

		// 背景
		D3DXVECTOR2 back_move;// 背景移動量

		back_move.x = back_move.y = 0;

		float scroll_speed = 3;         // スクロールスピード
		float width_speed = 3;

		const char *str[3] = {
			"ニーア2.jpg",
			"ニーアPC壁紙.jpg",
			"ファンタジー系空.jpg",
		};

		// 自機

		//Texture::Load("Boss_spider_attack1.png");
		Texture::Load("Boss_spider_attack1_resizse.png");
		Texture::Load("Title.png");

		int graph_num = 0;
		int timer = 0;

		while (ProcessMessage()==true) {

			// エスケープキー
			if (GetKeyState(VK_ESCAPE) & 0x8000) {
				break;
			}

			if (DrawStart() == true) {

				timer++;

				if (timer > 5) {
					graph_num++;
					timer = 0;
				}
				else if (graph_num >= 64) {
					graph_num=0;
				}

				// 横　37000 縦1024
				// 横516 縦30
				// 描画
				//Texture::Draw2D("Boss_spider_attack1.png", 1920/2,1080/2, -23000, 600, 0.5f, 0.5f, true, 46, 1, graph_num);

				// 46
				// 62

				// 横 32768
				// 縦 1024

				// 8192だと荒れない

				Texture::Draw2D("Boss_spider_attack1_resizse.png", 1920 / 2, 1080 / 2, -32068, 1, 0.5f, 0.5f, true, 64, 1, graph_num);
				//Texture::Draw2D("Title.png", 1920 / 2, (1080 / 2)+500, -7600, 1000, 0.5f, 0.5f, true, 16, 1, graph_num);

				DrawEnd();
			}
		}
	}
	*/


	// 今の位置より大きい場合は
	//if (back_pos.y > -SCREEN_HEIGHT * now_postion) {
	//	now_postion++;
	//}
	//// 今の位置より小さい場合は
	//else if (back_pos.y < -SCREEN_HEIGHT * now_postion &&
	//	now_postion!=0) {
	//	now_postion--;
	//}

	//now_postion = 0;

	// 背景を移動させる
	//for (int i = 0; i < DRAW_GRAPH_MAX; i++) {
	//
	//	Texture::Draw2D(str[3], 0, (-SCREEN_HEIGHT * now_postion) + back_pos.y, 1, 1, 0.f, 0.f);
	//
	//	now_postion++;
	//}
