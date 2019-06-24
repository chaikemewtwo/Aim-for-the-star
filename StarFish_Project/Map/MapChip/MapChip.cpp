#include"D3D9.h"
#include"../../Lib/Window/Window.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"
#include"../MapChip/MapChip.h"
#include"../../Player/Player.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include"../BackGround/BackGround.h"
#include<stdio.h>
#include<string>
#include"../MapCollision/MapCollider.h"
#include"../BedRockChip/RockChip.h"



// コンストラクタ
Map::Map(Player*star1,Player*star2,EnemyManager*e_mng,ObjectManager*obj_mng) {

	// インスタンス生成
	{
		// nullチェック
		if (e_mng == nullptr) {
			return;
		}
		if (star1 == nullptr) {
			return;
		}
		if (star2 == nullptr) {
			return;
		}
		if (obj_mng == nullptr) {
			return;
		}

		// 各インスタンス受け取り
		m_p_player[0] = star1;
		m_p_player[1] = star2;
		m_p_enemy_mng = e_mng;
		m_p_obj_mng = obj_mng;
		// マップ当たり判定クラスを生成
		m_p_map_collision = new MapCollider(this);
	}

	// マップ位置X初期化
	const float INIT_MAP_POS_X = 0.f; 
	// マップ位置Y初期化
	const float INIT_MAP_POS_Y = 0.f; 
	// マップ移動X初期化
	const float INIT_MAP_MOVE_X = 0.f;
	// マップ移動Y初期化
	const float INIT_MAP_MOVE_Y = 0.f;

	// ソートオブジェクト代入
	m_sort_object_type = MAX;

	// マップ座標の初期化X
	m_pos.x = INIT_MAP_POS_X;

	// マップ座標の初期化Y
	m_pos.y = INIT_MAP_POS_Y;		  

	// マップ座標移動座標初期化
	m_move.x = INIT_MAP_MOVE_X;
	m_move.y = INIT_MAP_MOVE_Y;
	
	// スクロールする範囲初期化
	m_scroll_range_up = SCROLL_RANGE_UP;
	m_scroll_range_down = SCROLL_RANGE_DOWN;

	// ファイル読み込み
	Load("Map/MapData/MapData.csv");
	
	// スクロールしているか
	m_is_scroll = true;

	// スクロール位置を中心に
	// 初期化時回りのオブジェクトを生成させる
	{
		int create_pos_begin = GetChipCastByPos(-m_pos.y);
		int create_pos_end = GetChipCastByPos(-m_pos.y) + (MAX_IN_WINDOW_CHIP_NUM_H + 2);

		for (int y = create_pos_begin; y < create_pos_end; y++) {
			for (int x = 0; x < MAX_IN_WINDOW_CHIP_NUM_W; x++){

				// 配列外アクセスは許させない
				if (y < 0 || x < 0) {
					return;
				}

				// 敵生成集め
				EnemyCreate(x, y);
				RockChipCreate(x, y);
			}
		}
	}	
}


Map::~Map() {

}


void Map::Update() {
	
	// マップの移動ベクトル初期化
	m_move.y = 0.f;
	
	// 先に衝突とスクロールをする
	for (int i = 0; i < 2; i++) {

		//if (m_move.y != 0.f) {
		//	m_p_player[i]->DBGSetGravityEnable(false);
		//}
		//else {
		//	m_p_player[i]->DBGSetGravityEnable(true);
		//}
		PlayerScroll(i);
		PlayerCollision(i);
	}
	PlayerScroll(0);
	PlayerCollision(0);
	
	// マップ座標にマップの移動ベクトルを加算
	m_pos.y += m_move.y;
	
	// スクロール制限
	MaxScroll();

	CreateAndDestory();
}


// マップの描画
void Map::Draw() {
}


void Map::PlayerCollision(int i) {

	/* プレイヤー座標 */
	// 自機の位置を代入,当たりポイントを補正
	D3DXVECTOR2 player_pos(m_p_player[i]->GetPos().x + VERTEX_OFFSET.x, m_p_player[i]->GetPos().y + VERTEX_OFFSET.y);   // 自機の位置
	D3DXVECTOR2 player_move(m_p_player[i]->GetMove().x, m_p_player[i]->GetMove().y);  // 自機の移動ベクトル
	
	m_p_map_collision->Collision(player_pos, player_move,collision_dir_type[i][0],collision_dir_type[i][1]);
	// マップの当たり判定
	//Collision(player_pos[i],player_move[i]);

	// プレイヤーの頂点位置をずらす
	player_pos -= VERTEX_OFFSET;

	// 自機(obj)の位置変更
	m_p_player[i]->SetPos(player_pos);
	// 自機の移動ベクトル変更
	m_p_player[i]->SetMove(player_move);
}


void Map::PlayerScroll(int i) {

	/* プレイヤー座標 */
	// 自機の位置を代入,当たりポイントを補正
	D3DXVECTOR2 player_pos(m_p_player[i]->GetPos().x + VERTEX_OFFSET.x, m_p_player[i]->GetPos().y + VERTEX_OFFSET.y);   // 自機の位置
	D3DXVECTOR2 player_move(m_p_player[i]->GetMove().x, m_p_player[i]->GetMove().y);  // 自機の移動ベクトル


	// スクロールしてもいいかどうか
	if (IsScroll() == true) {
		Scroll(&player_pos.y, &player_move.y);
	}

	// プレイヤーの頂点位置をずらす
	player_pos -= VERTEX_OFFSET;

	// 自機(obj)の位置変更
	m_p_player[i]->SetPos(player_pos);
	// 自機の移動ベクトル変更
	m_p_player[i]->SetMove(player_move);
}


void Map::Scroll(float *pos_y, float *move_y) {


	// 上のスクロール範囲に入ったら
	if (*pos_y <= m_scroll_range_up) {

		// スクリーン座標を戻す
		*pos_y = m_scroll_range_up;

		// 移動していないなら
			// マップ移動を加算
			m_move.y = *move_y;
		
	}

	// 下のスクロール範囲に入ったら
	else if (*pos_y >= m_scroll_range_down) {

		// スクリーン座標を戻す
		*pos_y = m_scroll_range_down;

		// 移動していないなら
			// マップ移動を加算
			m_move.y = *move_y;
	}
}


void Map::MaxScroll() {

	// 上の最大スクロール
	if (m_pos.y <= -BackGround::MAX_UP_SCROLL + 1.f) {

		m_scroll_range_up = 0.f;
		// スクロール移動初期化
		m_move.y = 0.f;
		// マップ座標初期化
		m_pos.y = -BackGround::MAX_UP_SCROLL - 1.f;

		// 最大スクロールにする
		m_is_max_scroll = true;
	}

	if(m_pos.y <= -BackGround::MAX_UP_SCROLL - 50.f){
		m_draw_range_up = SCROLL_RANGE_UP;
	}
	
	// 下の最大スクロール
	if (m_pos.y > 0.f) {

		m_scroll_range_down = 800.f;

		// スクロール移動初期化
		m_move.y = 0.f;
		// マップ座標初期化
		m_pos.y = 0.f;
	}
	else {
		// スクロールを最初に戻す
		m_draw_range_down = SCROLL_RANGE_DOWN;
	}
}


void Map::CreateAndDestory() {

	// 上の生成線
	const int CREATE_LINE_UP = 15;
	// 下の生成線
	const int CREATE_LINE_DOWN = 0;
	// 上の削除線
	const int DESTORY_LINE_UP = CREATE_LINE_UP +2;
	// 下の削除線
	const int DESTORY_LINE_DOWN = CREATE_LINE_DOWN-1;


	int create_line_range[2] = { CREATE_LINE_UP,CREATE_LINE_DOWN };
	// 生成
	{
		for (int i = 0; i < 2; i++) {
			
			MapObjectWidthCreateLine(
				GetChipCastByPos(-m_pos.y) + create_line_range[i]
			);
		}
	}

	int destory_line_range[2] = { DESTORY_LINE_UP ,DESTORY_LINE_DOWN };
	// 削除
	{
		for (int i = 0; i < 2; i++) {
			
			MapObjectWidthDestoryLine(
				GetChipCastByPos(-m_pos.y) + destory_line_range[i]
			);
		}
	}
}


void Map::MapObjectWidthCreateLine(int create_line_y) {

	// 配列外アクセスは許させない
	if (create_line_y < 0.f || create_line_y > m_max_height_map_size) {
		return;
	}

	for (int x = 0; x < Map::MAX_IN_WINDOW_CHIP_NUM_W; x++) {

		// 位置を代入
		D3DXVECTOR2 pos(
			(float)(Map::CHIP_SIZE * x),
			(Map::CHIP_SIZE * -create_line_y) + Window::HEIGHT - m_pos.y
		);

		// デバッグ用
		Texture::Draw2D("Resource/Texture/Map/chip-map_image_3.png",pos.x,pos.y - 64.f);

		// チップが活動中なら生成中止
		if (m_map_chip_list[m_max_height_map_size - create_line_y][x]->IsChipActive() == true) {
			continue;
		}

		// 敵生成
		EnemyCreate(x, create_line_y);
		// 岩生成
		RockChipCreate(x, create_line_y);
	}
}


void Map::MapObjectWidthDestoryLine(int destory_line_y) {


	// 配列外アクセスは許させない
	if (destory_line_y < 0 || destory_line_y > m_max_height_map_size) {
		return;
	}
	
	// 下から線を作成
	int destory_line = m_max_height_map_size - destory_line_y;

	// 生成部分(下から生成していく)
	for (int x = 0; x < Map::MAX_IN_WINDOW_CHIP_NUM_W; x++) {

		// 位置を代入
		D3DXVECTOR2 pos(
			(float)(Map::CHIP_SIZE * x),
			(Map::CHIP_SIZE * -destory_line_y) + Window::HEIGHT - m_pos.y
		);

		// デバッグ用
		Texture::Draw2D("Resource/Texture/Map/chip-map_image_10.png", pos.x, pos.y);

		// オブジェクトなら
		//if (m_map_chip_list[destory_line][x]->IsObject() == true) {
		//	continue;
		//}

		// チップが活動しているなら
		if (m_map_chip_list[destory_line][x]->IsChipActive() == true) {

			// 要素削除
			m_p_obj_mng->Exit(m_map_chip_list[destory_line][x]->GetId());
			// 番号を取り出す
			int chip_num = m_map_chip_list[destory_line][x]->GetChipNum();

			// 生成されているならメモリ削除
			if (m_map_chip_list[destory_line][x] != nullptr) {
				delete m_map_chip_list[destory_line][x];
			}

			// 初期状態に戻す
			m_map_chip_list[destory_line][x] = new ChipBase(chip_num);

			// チップ活動中止にする
			m_map_chip_list[destory_line][x]->SetIsChipActive(false);
		}
	}
}


void Map::EnemyCreate(int x, int y) {

	// チップ座標位置を作成
	D3DXVECTOR2 pos(
		(float)(Map::CHIP_SIZE * x),
		(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_pos.y);

	// 修正値
	D3DXVECTOR2 offset_pos(0.f, -148.f);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_max_height_map_size - y;

	
	// チップが活動中なら生成中止
	if (m_map_chip_list[create_chip_y][x]->IsChipActive() == true) {
		return;
	}

	// チップ番号をMapクラスから受け取る
	int chip_num = m_map_chip_list[create_chip_y][x]->GetChipNum();
	// 敵生成チップ番号
	int enemy_chip[3] = { 100,101,102 };
	// 敵の種類
	EnemyType enemy_type[3] = { SEAURCHIN ,NO_MOVE_SEAURCHIN , SELLFISH };

	// オブジェクト生成、チップ番号が100以上なら
	if (chip_num >= 100 &&
		chip_num <= 103) {

		// 敵生成
		for (int i = 0; i < 3; i++) {

			// 生成番号と一致していたら
			if (chip_num == enemy_chip[i]) {

				// 生成
				m_p_enemy_mng->CreateEnemy(pos + offset_pos,this, m_p_player[0], m_p_player[1], enemy_type[i]);
				// チップベースは生成中に変える
				m_map_chip_list[create_chip_y][x]->SetIsChipActive(true);
				m_map_chip_list[create_chip_y][x]->SetIsObject(true);

				break;
			}
		}

		// ブラインド生成
		if (chip_num == 103) {
	
			// 修正位置を少しずらす
			offset_pos.x += (float)Map::CHIP_SIZE + 600.f;
			// 生成
			m_p_enemy_mng->CreateBlind(pos + offset_pos, D3DXVECTOR2(-300.f,1000.f));
			// マップチップ記録
			m_map_chip_list[create_chip_y][x]->SetIsChipActive(true);
			m_map_chip_list[create_chip_y][x]->SetIsObject(true);
		}
	}
}


void Map::RockChipCreate(int x, int y) {

	// チップ座標位置を作成
	D3DXVECTOR2 pos(
		(float)(Map::CHIP_SIZE * x),
		(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_pos.y
	);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_max_height_map_size - y;

	// 指定のチップを渡す
	ChipBase*chip_base = m_map_chip_list[create_chip_y][x];

	// チップ番号をMapクラスから受け取る
	int chip_num = m_map_chip_list[create_chip_y][x]->GetChipNum();

	// チップが活動中なら生成中止
	if (chip_base->IsChipActive() == true) {
		return;
	}

	// 検索しているチップが岩のチップ番号なら
	if (chip_num != 0 && chip_num <= 10) {

		// 位置を補正
		pos.y -= 64.f;

		// チップリストの中にすでにチップがある場合
		if (m_map_chip_list[create_chip_y][x] != nullptr) {
			delete m_map_chip_list[create_chip_y][x];
		}

		// 岩リスト追加
		m_map_chip_list[create_chip_y][x] =
			new RockChip(
				chip_num,
				pos,
				this
			);

		// 岩盤登録
		m_p_obj_mng->Entry(m_map_chip_list[create_chip_y][x]);

		// マップチップ記録
		m_map_chip_list[create_chip_y][x]->SetIsChipActive(true);
	}
}


void Map::Load(const std::string&file_name) {

	// 文字列バッファ
	const int STRING_BUFFER = 256;
	// 10進数
	const int TenBaseNumber = 10;
	FILE*fp;                               // ストリーム
	const char *fname = file_name.c_str(); // ファイル名
	char file_load_buffer[STRING_BUFFER];  // ファイル読み込みバッファ 

	// ファイルオープン
	fopen_s(&fp, fname, "r");

	// ファイルが読み込まれてない場合
	if (fp == NULL) {
		return;
	}

	// 縦と横の現在チップ
	int height_chip = 0, width_chip = 0;

	// 文字列読み込み、改行まで
	while (fgets(file_load_buffer, 256, fp) != NULL) {

		// 最初が改行と空白なら戻す
		if (file_load_buffer[0] == '\n' || file_load_buffer[0] == '\0') {
			continue;
		}

		// チップ文字列をバッファにいれる
		char *chip_string = file_load_buffer;
		// 1次元配列に要素を追加
		m_map_chip_list.emplace_back();

		// 次の列へ
		while (*chip_string != '\0'&& *chip_string != '\n') {

			m_map_chip_list[height_chip].emplace_back();
			// 要素追加
			m_map_chip_list[height_chip][width_chip] = (new ChipBase());
			// 整数値変換してチップ番号に登録
			m_map_chip_list[height_chip][width_chip++]->SetChipNum(strtol(chip_string, &chip_string, TenBaseNumber));

			// 文字列加算
			chip_string++;
		}

		// 横チップ初期化
		width_chip = 0;
		// 縦チップを下へ動かす
		height_chip++;
	}

	/* ---前--- */
	//// 配列外アクセス防止に10配列余分に配列を取る
	//for (int i = 0; i < 10; i++) {
	//
	//	m_map_chip_list.insert(m_map_chip_list.begin() + 1, new MapChip);
	//	m_map_chip_list.at(i).insert(m_map_chip_list.begin() + 1,new MapChip);
	//
	//	for (int j = 0; j < MAX_IN_WINDOW_CHIP_NUM_W; j++) {
	//
	//		m_map_chip_list[0].front();
	//		// 要素追加
	//		m_map_chip_list[0][j] = new MapChip;
	//
	//		m_map_chip_list[0][j]->chip_num = 0;
	//	}
	//}

	/* ---後ろ--- */
	// 配列外アクセス防止に10配列余分に配列を取る
	for (int i = height_chip; i < 10 + height_chip; i++) {
	
		m_map_chip_list.emplace_back();
	
		for (int j = 0; j < MAX_IN_WINDOW_CHIP_NUM_W; j++) {
	
			m_map_chip_list[i].emplace_back();
			// 要素追加
			m_map_chip_list[i][j] = new ChipBase;
	
			m_map_chip_list[i][j]->SetChipNum(0);
		}
	}

	// 高さを記録
	m_max_height_map_size = height_chip;

	// ファイルを閉じる
	fclose(fp);
	return;
}


int Map::GetChipCastByPos(const float&pos)const {
	return static_cast<int>(std::floor(pos / CHIP_SIZE));
}


int Map::GetChipParam(const float  pos_x, const float pos_y) {

	// マップ座標変換
	int px = GetChipCastByPos(pos_x);
	int py = GetChipCastByPos(pos_y);

	// マップチップ範囲外なら戻す
	if (px < 0 || px >= MAX_IN_WINDOW_CHIP_NUM_W ||
		(m_max_height_map_size)+(py - MAX_IN_WINDOW_CHIP_NUM_H) < 0 || py > MAX_IN_WINDOW_CHIP_NUM_H) {
		return 0;
	}

	// マップの当たり判定をm_draw_mapに変更
	return m_map_chip_list[m_max_height_map_size + (py - MAX_IN_WINDOW_CHIP_NUM_H)][px]->GetChipNum();
}


float Map::GetChipPosCastByChip(const float &chip_pos, const float &chip_y)const {
	return (chip_pos * CHIP_SIZE);
}

int Map::GetMaxHeightMapSize()const {
	return m_max_height_map_size;
}

D3DXVECTOR2 Map::GetMove()const {
	return -m_move;// -をなくす
}

bool Map::IsScroll()const {
	return m_is_scroll;
}

bool Map::IsMaxScroll()const {
	return m_is_max_scroll;
}

void Map::SetIsScroll(bool is_scroll) {
	m_is_scroll = is_scroll;
}

void Map::ActiveChangeChipSelect(int y, int x,bool is_chip_active) {
	m_map_chip_list[y][x]->SetIsChipActive(is_chip_active);
}

bool Map::IsActiveChipSelect(int y, int x) {
	return m_map_chip_list[y][x]->IsChipActive();
}

int Map::GetChipNumChipSelect(int y, int x) {
	return m_map_chip_list[y][x]->GetChipNum();
}

void Map::PlusSignChange(float &sign_change_num) {
	sign_change_num *= -1;
}

float Map::GetScrollRangeUp() {
	return m_scroll_range_up;
}

float Map::GetScrollRangeDown() {
	return m_scroll_range_down;
}


//
//bool Map::IsStand()const {
//	return m_is_stand;
//}
//
//bool Map::IsWallCollision()const {
//	return m_is_wall_collision;
//}
//
//bool Map::IsWallColUp()const {
//	return m_is_wall_collision_up;
//}
//
//bool Map::IsWallColDown()const {
//	return m_is_wall_collision_down;
//}
//
//bool Map::IsWallColLeft()const {
//	return m_is_wall_collision_left;
//}
//
//bool Map::IsWallColRight()const {
//	return m_is_wall_collision_right;
//}


// 当たり判定を取っているサイズ
/*
縦128
横64
*/

/*
bool Map::Collision(D3DXVECTOR2&pos,D3DXVECTOR2&move) {

const float Resize = 1.f;  // サイズを修正
bool is_collision = false; // 当たっているかどうか

// 左上
D3DXVECTOR2 up_left(pos.x + Resize + CHIP_SCALE_X, pos.y + Resize + CHIP_SCALE_Y);
// 右上
D3DXVECTOR2 up_right(pos.x + CHIP_SIZE - Resize - CHIP_SCALE_X, pos.y + Resize + CHIP_SCALE_Y);
// 左下
D3DXVECTOR2 down_left(pos.x + Resize + CHIP_SCALE_X, pos.y + CHIP_SIZE - Resize - CHIP_SCALE_Y);
// 右下
D3DXVECTOR2 down_right(pos.x + CHIP_SIZE - Resize - CHIP_SCALE_X, pos.y + CHIP_SIZE - Resize - CHIP_SCALE_Y);

// Y座標当たり判定
{
// 衝突情報y座標
float collision_info_y[4][4] = {
{up_left.x,up_left.y,0.f,move.y},
{up_right.x,up_right.y,0.f,move.y},
{down_left.x,down_left.y + CHIP_SIZE,0.f,move.y},
{down_right.x,down_right.y + CHIP_SIZE,0.f,move.y},
};

// 上の衝突判定
if (IsFloorCollision(collision_info_y[0][0], collision_info_y[0][1],
collision_info_y[0][2], collision_info_y[0][3]) == true) {
is_collision = true;
// 立っている
m_is_stand = true;
}

// y軸の衝突判定(四隅)
for (int i = 1; i < 3; i++) {
if (IsFloorCollision(collision_info_y[i][0], collision_info_y[i][1],
collision_info_y[i][2], collision_info_y[i][3]) == true) {
is_collision = true;
}
}

// 衝突していたら
if (is_collision == true) {

// 縦の衝突判定
VerticalPosPullBack(pos.y, move.y);
// 衝突していないに変更
is_collision = false;
}
}

// y軸更新
up_left.y = pos.y + Resize + CHIP_SCALE_Y;
up_right.y = pos.y + Resize + CHIP_SCALE_Y;
down_left.y = pos.y + CHIP_SIZE - Resize - CHIP_SCALE_Y;
down_right.y = pos.y + CHIP_SIZE - Resize - CHIP_SCALE_Y;

// X座標当たり判定
{
// 衝突情報x座標
float collision_info_x[6][4] = {
{ up_left.x,up_left.y,move.x,0.f },
{ up_right.x,up_right.y,move.x,0.f },
{ down_left.x,down_left.y + CHIP_SIZE,move.x,0.f },
{ down_right.x,down_right.y + CHIP_SIZE,move.x,0.f },
{ down_left.x, down_right.y, move.x, 0.f },
{ down_right.x, down_right.y, move.x, 0.f },
};

for (int i = 0; i < 6; i++) {
if (IsFloorCollision(collision_info_x[i][0], collision_info_x[i][1],
collision_info_x[i][2], collision_info_x[i][3]) == true) {
is_collision = true;
}
}

if (is_collision == true) {
is_collision = false;
SidePosPullBack(pos.x, move.x);
}
}

return is_collision;
}


void Map::InitWallCollision() {

// 衝突していない
//m_is_wall_col[0] = false;
//m_is_wall_col[1] = false;
m_is_wall_collision_up = false;
m_is_wall_collision_down = false;
m_is_wall_collision_right = false;
m_is_wall_collision_left = false;
}


bool Map::IsFloorCollision(float pos_x, float pos_y,float move_x,float move_y) {

// 現在のスクリーン座標にマップ座標を加算する
D3DXVECTOR2 after_pos(pos_x + move_x ,pos_y + move_y + (m_pos.y) + m_move.y);

// 床と衝突しているか(障害物は50番号まで),0番号は何もなし
if (GetChipParam(after_pos.x, after_pos.y) <= 50 && GetChipParam(after_pos.x, after_pos.y) >= 1) {

// 衝突している
return true;
}
// 衝突していない
return false;
}


// 横マップの位置に修正
void Map::SidePosPullBack(float &pos_x, float &move_x) {


// 入ったマップチップの座標を割り出す
float chip_pos_x = 0;

// 左
if (move_x < 0.f) {

// チップに変換
chip_pos_x = (float)GetChipCastByPos(pos_x - (1));

// X位置を右に戻す
pos_x = (chip_pos_x * CHIP_SIZE) - move_x;

// 縮小する時
if (CHIP_SCALE_X > 0.f) {
pos_x += (CHIP_SIZE - CHIP_SCALE_X);
}

// 移動ベクトルなし
move_x = 0.f;
// 左に衝突
m_is_wall_collision_left = true;
}

// 右
else if (move_x > 0.f) {

chip_pos_x = (float)GetChipCastByPos(pos_x);
// 位置を戻す
pos_x = (chip_pos_x * CHIP_SIZE) + CHIP_SCALE_X - move_x;

// 移動ベクトルなし
move_x = 0.f;
// 右に衝突
m_is_wall_collision_right = true;
}
}


void Map::VerticalPosPullBack(float &pos_y, float &move_y) {


// 入ったマップチップの座標を割り出す
float chip_pos_y = 0.f;

// 上(自機の移動とマップの移動が進んだ時)
if (move_y < 0.f || m_move.y < 0.f) {

// チップサイズ割り出し
chip_pos_y = (float)GetChipCastByPos((pos_y +(m_pos.y)) - (move_y - 1 + CHIP_SCALE_Y));

// 下に戻す
pos_y = (chip_pos_y * CHIP_SIZE) + (-m_pos.y) - m_move.y;

// 拡縮Y
if (CHIP_SCALE_Y > 0.f) {
// 修正(自機の移動とマップの移動を加算)
pos_y += (CHIP_SIZE - CHIP_SCALE_Y);
}

// スクロール範囲に入っていれば
if (pos_y < m_scroll_range_up) {
m_pos.y += (pos_y - m_scroll_range_up);
}

// 移動ベクトルなし
move_y = 0.f;

// 上に衝突
m_is_wall_collision_up = true;
}

// 下(自機の移動とマップの移動が進んだ時)
else if (move_y > 0.f || m_move.y > 0.f) {

// チップサイズ割り出し
chip_pos_y = (float)GetChipCastByPos((pos_y + m_pos.y) + move_y);

// 上に戻す
pos_y = (chip_pos_y * CHIP_SIZE) + (-m_pos.y);

pos_y += -move_y - m_move.y;

// サイズY
if (CHIP_SCALE_Y > 0.f) {
pos_y += CHIP_SCALE_Y;
}

// スクロール範囲に入っていれば
if (pos_y > m_scroll_range_down) {
m_pos.y += (pos_y + m_scroll_range_down);
}

// 移動ベクトルなし
move_y = 0.f;

// 下に衝突
m_is_wall_collision_down = true;
}
}
*/



/*
// 生成は上と下のラインを作り、作成する。
// それぞれ範囲外にでたら、アクティブをfalseにする。

void Map::MapObjectCreate() {

	// 生成ライン
	int create_line[2];

	// 上
	create_line[0] = GetChipCastByPos(-m_pos.y) + 18;
	// 下
	create_line[1] = GetChipCastByPos(-m_pos.y) + 1;

	// 生成部分(下から生成していく)
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < MAX_IN_WINDOW_CHIP_NUM_W; x++) {

			int create_chip_y = (m_max_height_map_size)-create_line[y];

			// 配列外アクセスは許させない
			if (create_chip_y < 0 || x < 0) {
				return;
			}

			// チップが生成されているなら
			if (m_map_chip_list[create_chip_y][x].m_is_active != false) {
				continue;
			}

			// 位置を代入
			D3DXVECTOR2 pos((float)(CHIP_SIZE * x), (CHIP_SIZE * -create_line[y]) + Window::HEIGHT - m_pos.y);

			//Texture::Draw2D("Resource/Texture/Map/chip-map_image_3.png", pos.x,(float)CHIP_SIZE * -create_line[0] + Window::HEIGHT - m_pos.y);
			//Texture::Draw2D("Resource/Texture/Map/chip-map_image_4.png", pos.x,(float)CHIP_SIZE * -create_line[1] + Window::HEIGHT - m_pos.y);

			// 敵生成
			EnemyCreate(x, create_line[y], m_map_chip_list[create_chip_y][x].m_chip_num);
			// 岩生成
			RockChipCreate(x, create_line[y], m_map_chip_list[create_chip_y][x].m_chip_num);
		}
	}
}


void Map::EnemyCreate(int x, int y, int chip_num) {

	// 位置を代入
	D3DXVECTOR2 pos((float)(CHIP_SIZE * x), (CHIP_SIZE * -y) + Window::HEIGHT - m_pos.y);
	// 修正値
	D3DXVECTOR2 fix_pos(0.f, -148.f);

	int create_chip_y = m_max_height_map_size - y;

	// オブジェクト生成、チップ番号が100以上なら
	if (m_map_chip_list[create_chip_y][x].m_chip_num >= 100 && m_map_chip_list[create_chip_y][x].m_chip_num <= 104) {
		switch (chip_num) {
			// ウニ生成
		case 100:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos, this, m_p_player[0], m_p_player[1], SEAURCHIN);
			// マップチップ記録
			m_map_chip_list[create_chip_y][x].m_is_active = true;
			break;
			// 落ちていくウニ生成
		case 101:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos, this, m_p_player[0], m_p_player[1], NO_MOVE_SEAURCHIN);
			// マップチップ記録
			m_map_chip_list[create_chip_y][x].m_is_active = true;
			break;
			// 貝生成
		case 102:
			// 補正
			fix_pos.x += CHIP_SIZE - 12.f;
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos, this, m_p_player[0], m_p_player[1], SELLFISH);
			// マップチップ記録
			m_map_chip_list[create_chip_y][x].m_is_active = true;
			break;
			// 右下に行くブラインド生成
		case 103:
			fix_pos.x += (float)CHIP_SIZE + 600.f;
			// ブラインド生成
			m_p_enemy_mng->CreateBlind(pos + fix_pos, D3DXVECTOR2(-200.f, 1000.f));
			// マップチップ記録
			m_map_chip_list[create_chip_y][x].m_is_active = true;
			break;
		}
	}
}


void Map::RockChipCreate(int x, int y, int chip_num) {

	D3DXVECTOR2 pos((float)(CHIP_SIZE * x), (CHIP_SIZE * -y) + Window::HEIGHT - m_pos.y);
	int create_chip_y = m_max_height_map_size - y;

	// 岩盤 HACK 作成中
	if (m_map_chip_list[create_chip_y][x].m_chip_num != 0 && m_map_chip_list[create_chip_y][x].m_chip_num <= 10) {

		// 位置を補正
		pos.y -= 64.f;
		// 岩盤生成
		m_p_obj_mng->Entry(
			new BedRockChip(
				m_map_chip_list[create_chip_y][x].m_chip_num,
				pos,
				this
			)
		);
		// マップチップ記録
		m_map_chip_list[create_chip_y][x].m_is_active = true;
	}
}


void Map::MapObjectDestory() {

	// 削除ライン
	int destory_line[2];

	// 上
	destory_line[0] = GetChipCastByPos(-m_pos.y) + CHIP_RANGE_UP + 4;
	// 下
	destory_line[1] = GetChipCastByPos(-m_pos.y) + CHIP_RANGE_DOWN - 4;


	// 生成部分(下から生成していく)
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < MAX_IN_WINDOW_CHIP_NUM_W - 1; x++) {

			// 配列外アクセスは許させない
			if (m_max_height_map_size + destory_line[y] < 0 || x < 0) {
				return;
			}

			// チップが活動しているなら
			if (m_map_chip_list[(m_max_height_map_size - destory_line[y])][x].m_is_active == true) {
				// マップチップ活動中にする
				m_map_chip_list[(m_max_height_map_size - destory_line[y])][x].m_is_active = false;
			}
		}
	}
}
*/


/*
void Map::CenterStuckChip(float &pos_x, float &pos_y, float &move_x, float &move_y) {

// チップ位置を作る
int chip_right = GetChipCastByPos(pos_x) + 1;
int chip_left = GetChipCastByPos(pos_x);
int chip_up = GetChipCastByPos(pos_y + m_pos.y);// 位置を補正
int chip_down = GetChipCastByPos(pos_y + m_pos.y) + 1;

float hsize = (float)CHIP_SIZE / 2;

// 自機を中心位置にずらす処理を行う

// 上
if (move_y > 0.f) {

pos_y = (chip_up * (float)(CHIP_SIZE)) + hsize - m_pos.y;
}
// 下
else if (move_y < 0.f) {
pos_y = (chip_down * (float)(CHIP_SIZE)) - hsize - m_pos.y;
}

// 右
if (move_x > 0.f) {
pos_x = (chip_right * (float)CHIP_SIZE) - hsize;
}
// 左
else if (move_x < 0.f) {
pos_x = (chip_left * (float)CHIP_SIZE) + hsize;
}
}
*/


/*
void Map::CreateGather(int x, int y, int chip_num) {

// 位置を代入
D3DXVECTOR2 pos((float)(CHIP_SIZE * x), (CHIP_SIZE * -y) + Window::HEIGHT - m_pos.y);
// 修正値
D3DXVECTOR2 fix_pos(0.f, -148.f);

int create_chip_y = m_max_height_map_size - y;

// オブジェクト生成、チップ番号が100以上なら
if (m_map_chip_list[create_chip_y][x].m_chip_num >= 100 && m_map_chip_list[create_chip_y][x].m_chip_num <= 104) {
switch (chip_num) {
// ウニ生成
case 100:
// 敵生成
e_p_mng->CreateEnemy(pos + fix_pos, this, m_p_base[0], m_p_base[1], SEAURCHIN);
// マップチップ記録
m_map_chip_list[create_chip_y][x].m_is_active = true;
break;
// 落ちていくウニ生成
case 101:
// 敵生成
e_p_mng->CreateEnemy(pos + fix_pos, this, m_p_base[0], m_p_base[1], NO_MOVE_SEAURCHIN);
// マップチップ記録
m_map_chip_list[create_chip_y][x].m_is_active = true;
break;
// 貝生成
case 102:
// 補正
fix_pos.x += CHIP_SIZE - 12.f;
// 敵生成
e_p_mng->CreateEnemy(pos + fix_pos, this, m_p_base[0], m_p_base[1], SELLFISH);
// マップチップ記録
m_map_chip_list[create_chip_y][x].m_is_active = true;
break;
// 右下に行くブラインド生成
case 103:
fix_pos.x += (float)CHIP_SIZE + 600.f;
// ブラインド生成
e_p_mng->CreateBlind(pos + fix_pos, D3DXVECTOR2(-100.f, 1000.f));
// マップチップ記録
m_map_chip_list[create_chip_y][x].m_is_active = true;
break;
}
}
// 岩盤 HACK 作成中
else if (m_map_chip_list[create_chip_y][x].m_chip_num != 0 && m_map_chip_list[create_chip_y][x].m_chip_num <= 10) {

// 位置を補正
pos.y -= 64.f;
// 岩盤生成
m_p_obj_mng->Entry(
new BedRockChip(
m_map_chip_list[create_chip_y][x].m_chip_num,
pos,
this
)
);
// マップチップ記録
m_map_chip_list[create_chip_y][x].m_is_active = true;
}
}*/


/*
bool NullCheck(Object*object) {

if (object == nullptr) {
return false;
}
return true;
}
*/

/*
// スクロールが上下行われているなら
bool Map::IsScrollLimit(float &pos_y1, float &pos_y2, D3DXVECTOR2&move1, D3DXVECTOR2&move2) {


	// 自機1が上、自機2が下の場合スクロール停止
	if (pos_y1 <= m_scroll_range_up && m_scroll_range_down <= pos_y2 &&
		IsWallCollision() == true) {

		// 位置を補正
		if (pos_y1 <= m_scroll_range_up) {
			pos_y1 = m_scroll_range_up;
		}
		if (pos_y2 >= m_scroll_range_down) {
			pos_y2 = m_scroll_range_down;
		}
		// マップ位置変換
		m_pos.y += move2.y;

		move1.y = 0.f;
		move2.y = 0.f;

		return false;
	}

	// 自機1が下,自機2が上の場合スクロール停止
	if (pos_y2 <= m_scroll_range_up && m_scroll_range_down <= pos_y1) {

		if (pos_y2 <= m_scroll_range_up) {
			pos_y2 = m_scroll_range_up;
		}
		if (pos_y1 >= m_scroll_range_down) {
			pos_y1 = m_scroll_range_down;
		}
		move2.y = 0.f;
		move1.y = 0.f;

		return false;
	}

	return true;
}
*/


//
//chip_u[0] = -0.001f;
//chip_v[1] = -0.01f;
//chip_u[1] = -0.01f;
//chip_v[2] = -0.01f;
//chip_v[7] = -0.01f;
//chip_v[4] = -0.001f;
//chip_v[3] = 0.01f;
//chip_v[5] = -0.01f;
//chip_v[6] =   - 0.001f;
//
//chip_u[4] = -0.01f;
//chip_u[5] = -0.01f;

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