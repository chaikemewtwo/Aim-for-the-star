#include"D3D9.h"
#include"../../Lib/Window/Window.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"
#include"../Map/Map.h"
#include"../../Player/Player.h"
#include"../../Player/PlayerManager.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include"../BackGround/BackGround.h"
#include<stdio.h>
#include<string>
#include"../MapCollision/MapCollider.h"
#include"../Chip/RockChip/RockChip.h"
#include"../Chip/NormalChip/NormalChip.h"



// コンストラクタ
Map::Map(EnemyManager*e_mng,ObjectManager*obj_mng) :
	m_scroll_move(0.f),
	m_scroll_pos(0.f),
	m_is_scroll(true)
{

	// nullチェック
	if (e_mng == nullptr) {
		return;
	}
	if (obj_mng == nullptr) {
		return;
	}

	// 各インスタンス受け取り
	m_p_enemy_manager = e_mng;
	m_p_obj_mng = obj_mng;

	// マップ当たり判定クラスを生成
	m_p_map_collider = new MapCollider(this);

	for (int i = 0; i < 2; i++) {
		collision_dir_type[0][i] = CollisionDirectionType::NONE;
		collision_dir_type[1][i] = CollisionDirectionType::NONE;
	}

	// スクロールする範囲初期化
	m_scroll_up_map_line = INIT_SCROLL_RANGE_UP;
	m_scroll_down_map_line = INIT_SCROLL_RANGE_DOWN;

	// ファイル読み込み
	Load("Map/MapData/MapData.csv");
}


Map::~Map() {

}


void Map::Init() {

	// スクロール位置を中心に
	// 初期化時回りのオブジェクトを生成させる
	{
		int create_pos_begin = GetChipCastByPos(-m_scroll_pos);
		int create_pos_end = GetChipCastByPos(-m_scroll_pos) + (MAX_IN_WINDOW_CHIP_NUM_H + 2);

		for (int y = create_pos_begin; y < create_pos_end; y++) {
			for (int x = 0; x < MAX_IN_WINDOW_CHIP_NUM_W; x++) {

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

void Map::Update() {
	
	// マップ座標にマップの移動ベクトルを加算
	m_scroll_pos += m_scroll_move;

	// マップの移動ベクトル初期化
	m_scroll_move = 0.f;

	// 生成と削除
	CreateAndDestory();
}


// マップの描画
void Map::Draw() {
}


void Map::CreateAndDestory(){

	// 上の生成線
	const int CREATE_LINE_UP = 18;
	// 下の生成線
	const int CREATE_LINE_DOWN = -1;

	// 上の削除線
	const int DESTORY_LINE_UP = CREATE_LINE_UP + 6;
	// 下の削除線
	const int DESTORY_LINE_DOWN = CREATE_LINE_DOWN - 6;


	// 生成線
	int create_line_range[2] = { CREATE_LINE_UP,CREATE_LINE_DOWN };

	// 生成
	{
		for (int i = 0; i < 2; i++) {
			
			MapObjectWidthEntryLine(
				(int)(std::ceil((-m_scroll_pos)) / CHIP_SIZE) + create_line_range[i]
			);
		}
	}

	// 削除線
	int destory_line_range[2] = { DESTORY_LINE_UP ,DESTORY_LINE_DOWN };

	// 削除
	{
		for (int i = 0; i < 2; i++) {
			
			MapObjectWidthExitLine(
				(int)(std::ceil((-m_scroll_pos)) / CHIP_SIZE) + destory_line_range[i]
			);
		}
	}
}


void Map::MapObjectWidthEntryLine(int create_line_y) {

	// 配列外アクセスは許させない
	if (create_line_y < 0.f || create_line_y > m_max_map_chip_height_size) {
		return;
	}

	for (int x = 0; x < Map::MAX_IN_WINDOW_CHIP_NUM_W; x++) {

		// チップが活動中なら生成中止
		if (m_map_chip_list[m_max_map_chip_height_size - create_line_y][x]->IsChipActive() == true) {
			continue;
		}

		// 敵生成
		EnemyCreate(x,create_line_y);
		// 岩生成
		RockChipCreate(x,create_line_y);
	}
}


void Map::MapObjectWidthExitLine(int destory_line_y) {


	// 配列外アクセスは許させない
	if (destory_line_y < 0 || destory_line_y > m_max_map_chip_height_size) {
		return;
	}
	
	// 下から線を作成
	int destory_line = m_max_map_chip_height_size - destory_line_y;

	// 生成部分(下から生成していく)
	for (int x = 0; x < Map::MAX_IN_WINDOW_CHIP_NUM_W; x++) {

		// 位置を代入
		D3DXVECTOR2 pos(
			(float)(Map::CHIP_SIZE * x),
			(Map::CHIP_SIZE * -destory_line_y) + Window::HEIGHT - (m_scroll_pos)
		);

		// 敵なら
		if (m_map_chip_list[destory_line][x]->IsEnemy() == true){

			// 敵削除
			m_map_chip_list[destory_line][x]->SetIsChipActive(false);
			m_map_chip_list[destory_line][x]->SetIsObject(false);
			continue;
		}
		
		// チップが活動しているなら
		else if (m_map_chip_list[destory_line][x]->IsChipActive() == true) {

			// オブジェクトに登録されているチップの要素削除
			m_p_obj_mng->Exit(m_map_chip_list[destory_line][x]);

			// 番号を取り出す
			int chip_num = m_map_chip_list[destory_line][x]->GetChipNum();

			// 生成されているならメモリ削除
			if (m_map_chip_list[destory_line][x] != nullptr) {
				delete m_map_chip_list[destory_line][x];
			}

			// 初期状態に戻す
			m_map_chip_list[destory_line][x] = new NormalChip(chip_num);

			// チップ活動中止にする
			m_map_chip_list[destory_line][x]->SetIsChipActive(false);
		}
	}
}


void Map::RockChipCreate(int x, int y) {
	
	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_max_map_chip_height_size - y;
	
	// チップ座標位置を作成
	D3DXVECTOR2 chip_pos(
		(float)(Map::CHIP_SIZE * x),
		(float)((Map::CHIP_SIZE) * -y) + 
		(float)(Window::HEIGHT + 8) + (CHIP_SIZE * ((-m_scroll_pos) / CHIP_SIZE)) - CHIP_SIZE
	);

	// チップ番号をMapクラスから受け取る
	int chip_num = m_map_chip_list[create_chip_y][x]->GetChipNum();

	// 検索しているチップが岩のチップ番号なら
	if (chip_num != 0 && chip_num <= 10) {

		// チップリストの中にすでにチップがある場合
		if (m_map_chip_list[create_chip_y][x] != nullptr) {
			delete m_map_chip_list[create_chip_y][x];
		}

		// 岩リスト追加
		m_map_chip_list[create_chip_y][x] = 
			new RockChip(
				chip_num,
				chip_pos,
				this
			);

		// 岩盤登録
		m_p_obj_mng->Entry(m_map_chip_list[create_chip_y][x]);

		// マップチップ記録
		m_map_chip_list[create_chip_y][x]->SetIsChipActive(true);
	}
}


void Map::EnemyCreate(int x, int y) {

	// チップ座標位置を作成
	D3DXVECTOR2 pos(
		(float)(Map::CHIP_SIZE * x),
		(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_scroll_pos
	);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_max_map_chip_height_size - y;

	// チップ番号をMapクラスから受け取る
	int chip_num = m_map_chip_list[create_chip_y][x]->GetChipNum();

	// 敵の修正位置
	D3DXVECTOR2 offset_pos[EnemyType::ENEMYTYPE_MAX] = 
	{ { 0.f,-64.f },
	{ -32.f,-96.f },
	{ 64.f, -64.f },
	{ 0.f,0.f },
	};

	// 敵生成チップ番号
	int enemy_chip[EnemyType::ENEMYTYPE_MAX] = {100,101,102,103};

	// 敵の種類
	EnemyType enemy_type[EnemyType::ENEMYTYPE_MAX] = { SEAURCHIN ,NO_MOVE_SEAURCHIN , SELLFISH ,NAPOREONFISH};

	// オブジェクト生成、チップ番号が100以上なら
	if (chip_num >= 100 &&
		chip_num <= 104) {

		// 敵生成
		for (int i = 0; i < EnemyType::ENEMYTYPE_MAX; i++){

			// 生成番号と一致していたら
			if (chip_num == enemy_chip[i]){

				// 生成
				m_p_enemy_manager->CreateEnemy(pos + offset_pos[i],this,enemy_type[i]);

				// チップベースは生成中に変える
				m_map_chip_list[create_chip_y][x]->SetIsChipActive(true);
				m_map_chip_list[create_chip_y][x]->SetIsObject(true);

				break;
			}
		}

		// ブラインド生成
		if (chip_num == 104) {

			// 修正位置を少しずらす
			D3DXVECTOR2 blind_offset_pos((float)Map::CHIP_SIZE + 600.f, 0.f);
			// 生成
			m_p_enemy_manager->CreateBlind(pos + blind_offset_pos, D3DXVECTOR2(-300.f, 1000.f));
			// マップチップ記録
			m_map_chip_list[create_chip_y][x]->SetIsChipActive(true);
			m_map_chip_list[create_chip_y][x]->SetIsObject(true);
		}
	}
}


void Map::Load(const std::string&load_file_name) {

	// 文字列バッファ
	const int STRING_BUFFER = 256;
	// 10進数
	const int TenBaseNumber = 10;
	// ファイルストリーム
	FILE*fp;                               
	// ファイル名
	const char *fname = load_file_name.c_str(); 
	// ファイル読み込みバッファ 
	char file_load_buffer[STRING_BUFFER];  

	// ファイルオープン
	fopen_s(&fp, fname, "r");

	// ファイルが読み込まれてない場合終了
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

			// 2次元配列に要素を追加
			m_map_chip_list[height_chip].emplace_back();

			// 要素追加
			m_map_chip_list[height_chip][width_chip] = new NormalChip();

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
	
	// 配列外アクセス防止に10配列余分に配列を取る
	for (int i = height_chip; i < 10 + height_chip; i++) {
	
		m_map_chip_list.emplace_back();
	
		for (int j = 0; j < MAX_IN_WINDOW_CHIP_NUM_W; j++) {
	
			m_map_chip_list[i].emplace_back();
			// 要素追加

			m_map_chip_list[i][j] = new NormalChip();
	
			m_map_chip_list[i][j]->SetChipNum(0);
		}
	}

	// 高さを記録
	m_max_map_chip_height_size = height_chip;

	// ファイルを閉じる
	fclose(fp);
	return;
}


int Map::GetChipParam(const float  pos_x, const float pos_y) {

	// マップ座標変換
	int px = GetChipCastByPos(pos_x);
	int py = GetChipCastByPos(pos_y);

	// マップチップ範囲外なら戻す
	if (px < 0 || px >= MAX_IN_WINDOW_CHIP_NUM_W ||
		(m_max_map_chip_height_size)+(py - MAX_IN_WINDOW_CHIP_NUM_H) < 0 || py > MAX_IN_WINDOW_CHIP_NUM_H) {
		return 0;
	}

	// マップの当たり判定をm_draw_mapに変更
	return m_map_chip_list[m_max_map_chip_height_size + (py - MAX_IN_WINDOW_CHIP_NUM_H)][px]->GetChipNum();
}

int Map::GetChipCastByPos(const float&pos)const {
	return static_cast<int>(std::floor((pos / CHIP_SIZE)));
}

int Map::GetChipCastByPos(const int&pos)const {
	return (pos / CHIP_SIZE);
}

int Map::GetChipPosCastByChip(const float chip_pos, const float chip_y)const {
	return (int)(chip_pos * CHIP_SIZE);
}

int Map::GetMaxMapChipHeightSize()const {
	return m_max_map_chip_height_size;
}

float Map::GetMove()const {
	return -m_scroll_move;
}

bool Map::IsScroll()const {
	return m_is_scroll;
}

float Map::GetSignChange(float sign_change_num) {
	return (sign_change_num *= -1);
}

float Map::GetScrollUpMapPosY() {
	return m_scroll_up_map_line;
}

float Map::GetScrollDownMapPosY() {
	return m_scroll_down_map_line;
}

float Map::GetPos()const {
	return m_scroll_pos;
}

void Map::SetPos(const float&pos) {
	m_scroll_pos = pos;
}

void Map::SetScrollMove(const float&move) {
	m_scroll_move = move;
}

void Map::SetScrollUpLine(const float &scroll_line_y) {
	m_scroll_up_map_line = scroll_line_y;
}

void Map::SetScrollDownLine(const float&scroll_line_y) {
	m_scroll_down_map_line = scroll_line_y;
}

MapCollider *Map::GetMapColliderInstance(){
	return m_p_map_collider;
}

// 当たり判定を取っているサイズ
/*
縦128
横64
*/
