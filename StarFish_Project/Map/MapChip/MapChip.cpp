#include"D3D9.h"
#include"../../Lib/Window/Window.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"
#include"../MapChip/MapChip.h"
#include"../../Player/Star1/Star1.h"
#include"../../Player/Star2/Star2.h"
#include"../../DebugFont/oxdebugfont.h"
#include"../../ProtoTypeEnemy/EnemyManager.h"

// バグの報告

// スクロールのバグ
// 上下ヒトデが行ったらバグった

// スクロールで下と上に強制的に言ったらバグった

// チップをでかくする

// structでチップに情報を持たせた方がいい

// マップチップオブジェクト配置

// MEMO
// 64ピクセル /* 横30 縦16 *//* 1088*/
// 128ピクセル/* 横15 縦8 *//*1024*/


// 2枚の背景でいける
// 当たり判定はずらした分だけ戻ってもいい


// コンストラクタ
MapChip::MapChip(Star1*star1,Star2*star2,EnemyManager*e_mng) {

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

	// 描画領域初期化
	m_draw_range_begin = 0.f;
	m_draw_range_end = 0.f;

	// ファイル読み込み
	Load("Map/MapData/MapData.csv");

	// デバッグ初期化
	m_py = 0;
	m_chip_num = 0;
}


void MapChip::Load(const std::string&file_name) {

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


void MapChip::Update() {

	// どこから描画するかを初期化
	m_draw_range_begin = GetChipCastByPos(-m_map_pos.y);                      // 描画のし始め 
	m_draw_range_end = GetChipCastByPos(-m_map_pos.y) + (MAX_CHIP_NUM_H + 1); // 描画の終わり

	// オブジェクトの生成
	ObjectCreate();

	// 初期化
	m_map_move_pos.x = m_map_move_pos.y = 0.f;

	for (int i = 0; i < 2; i++) {
		m_move_pos[i].x = m_move_pos[i].y = 0.f;
		m_obj_pos[i].x = m_obj_pos[i].y = 0.f;
	}

	// HACK 同じ処理を一つにまとめなければならない
	// 自機1の当たり判定処理
	
	for (int i = 0; i < 2; i++) {// 一旦当たり判定を一つにする

		// マップチップの位置変更
		m_obj_pos[i].x = m_pbase[i]->GetPos().x + HIT_POINT_X;
		m_obj_pos[i].y = m_pbase[i]->GetPos().y + HIT_POINT_Y;

		// 移動位置変更
		m_move_pos[i] = m_pbase[i]->GetMovePos();

		// 当たり判定
		MapCollision(i);

		// スクロールライン
		DrawLineIsActive(m_obj_pos[i].y,m_move_pos[i].y,m_scroll_range_up,m_scroll_range_down);

		// 当たり位置を決める。
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


// マップの描画
void MapChip::Draw() {


	// MEMO マップチップ番号の敵が生成されている場合は生成しない感じにしたらいい

	for (int y = m_draw_range_begin; y < m_draw_range_end; y++) {
		for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

			// 配列外アクセスは許させない
			if ((m_height_map_num)-y < 0 || x < 0) {
				return;
			}

			// ブロック
			if (m_map[(m_height_map_num)-y][x].m_chip_num == 1) {

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
			m_draw_range_begin - m_draw_range_end
			);

		// お試し描画
		//OX::DebugFont::print(
		//	500,
		//	500,
		//	0x000ffff,
		//	"current_chip => %d",
		//	(int)(m_height_map_num + 1) + (m_py - MAX_CHIP_NUM_H));

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

		OX::DebugFont::print(
			500,
			620,
			0x000ffff,
			"m_draw_range_begin => %f",
			m_draw_range_begin
		);

		OX::DebugFont::print(
			500,
			640,
			0x000ffff,
			"m_draw_range_end => %f",
			m_draw_range_end
		);
}



// 遷移はy軸だけ
int MapChip::DrawLineIsActive(float&pos_y, float&move_y, float up_range, float down_range) {

	// 描画遷移範囲 = 現在のマップ座標(本来はスクリーン座標の方がいい) + 遷移範囲(スクリーンから見て)

	// 上の遷移基準
	if (pos_y < up_range) {
		// スクリーン座標を戻す
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


void MapChip::LandOnTheGround() {

	// 着地点に着地したら
	if (m_map_pos.y > INIT_MAP_POS_Y) {

		m_map_pos.y = INIT_MAP_POS_Y;
		m_move_pos[0].y = 0.f;
		m_move_pos[1].y = 0.f;
	}
}


void MapChip::ObjectCreate() {

	int draw_range_begin = GetChipCastByPos(-m_map_pos.y);                   // 描画のし始め 
	int draw_range_end = GetChipCastByPos(-m_map_pos.y) + (MAX_CHIP_NUM_H + 1); // 描画の終わり

	for (int y = draw_range_begin; y < draw_range_end; y++) {
		for (int x = 0; x < MAX_CHIP_NUM_W; x++) {

			// 配列外アクセスは許させない
			if (m_height_map_num - y < 0 || x < 0) {
				return;
			}

			// オブジェクト生成、idの場所が0以上なら
			if (m_map[m_height_map_num - y][x].m_chip_num == 2) {

				// 位置を代入
 				D3DXVECTOR2 pos((CHIP_SIZE * x), (CHIP_SIZE * -y) + 1080 - m_map_pos.y);

				if (m_map_chip_id[m_height_map_num - y] == 0){
					// 敵生成
 					e_pmng->Create(pos,this);
					// マップチップ記録
					m_map_chip_id[m_height_map_num - y] = m_map[m_height_map_num - y][x].m_chip_num;
				}
				// 番号が入っていたら
				else {
					
				}
			}
		}
	}
}

// 先にx次にyを調べるようにさせる
// 衝突した後に移動方向を調べるか逆か
// 当たった後に移動方向を調べればはじける

// 0番目がバグっている
void MapChip::MapCollision(int i) {

	// 当たり判定
	// 4隅を調べている、当たり判定後の処理に移動方向で戻すのを決める。
	// CHIP_SIZE * 2は128の高さで当たり判定を取っている為

	const float RS = 1.f;            // ResizeのRS.サイズを補正

	// 左上
	D3DXVECTOR2 up_left(m_obj_pos[i].x + RS + SHRINK_X, m_obj_pos[i].y + RS + SHRINK_Y);
	// 右上
	D3DXVECTOR2 up_right(m_obj_pos[i].x + CHIP_SIZE - RS - SHRINK_X, m_obj_pos[i].y + RS + SHRINK_Y);
	// 左下
	D3DXVECTOR2 down_left(m_obj_pos[i].x + RS + SHRINK_X, m_obj_pos[i].y + CHIP_SIZE - RS - SHRINK_Y);
	// 右下
	D3DXVECTOR2 down_right(m_obj_pos[i].x + CHIP_SIZE - RS - SHRINK_X, m_obj_pos[i].y + CHIP_SIZE - RS - SHRINK_Y);
	
	// y軸の衝突判定(四隅)
	if (IsFloorCollision(up_left.x,up_left.y, 0.f, m_move_pos[i].y) == true ||
		IsFloorCollision(up_right.x,up_right.y, 0.f, m_move_pos[i].y) == true ||		
		IsFloorCollision(down_left.x,down_left.y + CHIP_SIZE, 0.f, m_move_pos[i].y) == true ||// 衝突点を1CHIP下にずらしている
		IsFloorCollision(down_right.x,down_right.y + CHIP_SIZE, 0.f, m_move_pos[i].y) == true) {
	
		// 縦の衝突判定
		NowPosYFixToMapPos(m_obj_pos[i].y, m_move_pos[i].y); // 縦にずらす
	}

	// y軸変更
	up_left.y = m_obj_pos[i].y + RS;
	up_right.y = m_obj_pos[i].y + RS;
	down_left.y = m_obj_pos[i].y + CHIP_SIZE - RS;
	down_right.y = m_obj_pos[i].y + CHIP_SIZE - RS;

	// ここでif文を作って四角形で当たっている場所をマップチップの当たり判定に埋め込んだらいいかも
	// x軸の衝突判定(四隅)
	if (IsFloorCollision(up_left.x, up_left.y, m_move_pos[i].x,0.f) == true ||
		IsFloorCollision(up_right.x, up_right.y, m_move_pos[i].x,0.f) == true ||
		IsFloorCollision(down_left.x, down_left.y + CHIP_SIZE,m_move_pos[i].x,0.f) == true ||// 衝突点を1CHIP下にずらしている
		IsFloorCollision(down_right.x, down_right.y + CHIP_SIZE ,m_move_pos[i].x,0.f) == true) {
		
	    // 横の衝突後の判定(衝突応答)
		NowPosXFixToMapPos(m_obj_pos[i].x, m_move_pos[i].x);// 横にずらす
	}
	// x軸の中心衝突判定
	else if (IsFloorCollision(down_left.x,down_right.y, m_move_pos[i].x, 0.f) == true ||// 左下
		IsFloorCollision(down_right.x,down_right.y, m_move_pos[i].x, 0.f) == true) {  // 右下
	
		NowPosXFixToMapPos(m_obj_pos[i].x, m_move_pos[i].x);// 横にずらす
	}
}


bool MapChip::IsFloorCollision(float pos_x, float pos_y,float move_x,float move_y) {

	// 現在のスクリーン座標にマップ座標を加算する
	D3DXVECTOR2 after_pos(pos_x + move_x,pos_y + move_y + (m_map_pos.y) + m_map_move_pos.y);

	// 床と衝突しているか
	if (GetChipParam(after_pos.x, after_pos.y) == 1) {

		// 衝突している
		return true;
	}
	
	// 衝突していない
	return false;
}

// 現在位置Xをマップ位置に修正
//Correct current position X to map position
// 横マップの位置に修正
void MapChip::NowPosXFixToMapPos(float &pos_x, float &move_x) {

	// 修正定数
	const int RETOUCH = 1;
	// 入ったマップチップの座標を割り出す
	float chip_pos_x = 0;

	// 左
	if (move_x < 0.f) {

		chip_pos_x = (float)GetChipCastByPos(pos_x - (move_x - RETOUCH));

		pos_x = (chip_pos_x * CHIP_SIZE);

		// 移動ベクトルなし
		move_x = 0.f;
	}

	// 右
	else if (move_x > 0.f) {

 		chip_pos_x = (float)GetChipCastByPos(pos_x + move_x);
		// 位置を戻す
		pos_x = (chip_pos_x * CHIP_SIZE);

		// 移動ベクトルなし
		move_x = 0.f;
	}
}


void MapChip::NowPosYFixToMapPos(float &pos_y, float &move_y) {

	// 修正定数
	const int RETOUCH = 1;
	// 入ったマップチップの座標を割り出す
	float chip_pos_y = 0;

	// 上
	if (move_y < 0.f) {
		// チップサイズ割り出し
		chip_pos_y = (float)GetChipCastByPos((pos_y +(m_map_pos.y)) - (move_y - RETOUCH));

		pos_y = (chip_pos_y * CHIP_SIZE) + (-m_map_pos.y) +0.5f;

		// スクロール範囲に入っていれば
		if (pos_y < m_scroll_range_up) {
			m_map_pos.y += (pos_y - m_scroll_range_up);
		}
		
		// 移動ベクトルなし
		move_y = 0.f;
	}

	// 下
	else if (move_y > 0.f) {
		// チップサイズ割り出し
		chip_pos_y = (float)GetChipCastByPos((pos_y + m_map_pos.y)+ move_y);

		pos_y = (chip_pos_y * CHIP_SIZE) + (-m_map_pos.y);

		// スクロール範囲に入っていれば
		if (pos_y > m_scroll_range_down) {
			m_map_pos.y += (pos_y + m_scroll_range_down);
		}

		// 移動ベクトルなし
		move_y = 0.f;
	}
}

// セルに変換
int MapChip::GetChipCastByPos(const float&pos)const{
	return static_cast<int>(std::floor(pos / CHIP_SIZE));
}


// 座標を入れたらマップチップの位置を返す
int MapChip::GetChipParam(const float &pos_x, const float&pos_y) {

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
float MapChip::GetChipPosCastByChip(const float &chip_pos, const float &chip_y)const{
	
	return (chip_pos * CHIP_SIZE);
}

// マップのリセット
void MapResat() {

}

// アクセサ
D3DXVECTOR2 MapChip::GetMapPos()const{
	return -m_map_pos;
}
D3DXVECTOR2 MapChip::GetMapMovePos()const {
	return -m_map_move_pos;
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
