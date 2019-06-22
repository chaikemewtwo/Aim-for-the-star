#include"../MapObjectFactory/MapObjectFactory.h"




MapObjectFactory::MapObjectFactory(Map*map, EnemyManager*enemy_mng, Player * player1, Player * player2, ObjectManager*obj_mng) {

	// 各インスタンスのnullチェック
	if (map == nullptr) {
		return;
	}
	if (enemy_mng == nullptr) {
		return;
	}
	if (player1 == nullptr) {
		return;
	}
	if (player2 == nullptr) {
		return;
	}
	if (obj_mng == nullptr) {
		return;
	}

	// 各インスタンスの代入
	m_p_map = map;
	m_p_enemy_mng = enemy_mng;
	m_p_player[0] = player1;
	m_p_player[1] = player2;
	m_p_obj_mng = obj_mng;
}


void MapObjectFactory::Init() {

	// 初期位置だけスクリーン画面にある全てのマップオブジェクトを生成する
	for (int i = 0; i < Map::MAX_IN_WINDOW_CHIP_NUM_W; i++) {
		CreateWidthLine(m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + i);
	}

}


void MapObjectFactory::Update() {

	// 上の生成線
	const int CREATE_LINE_UP = 16;
	// 下の生成線
	const int CREATE_LINE_DOWN = 3;
	// 上の削除線
	const int DESTORY_LINE_UP = CREATE_LINE_UP + 1;
	// 下の削除線
	const int DESTORY_LINE_DOWN = CREATE_LINE_DOWN - 1;

	int create_line_range[2] = { CREATE_LINE_UP,CREATE_LINE_DOWN };
	// 生成
	{
		for (int i = 0; i < 2; i++) {
			// 上
			CreateWidthLine(
				m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + create_line_range[i]
			);
		}
	}
	
	int destory_line_range[2] = { DESTORY_LINE_UP ,DESTORY_LINE_DOWN };
	// 削除
	{
		for (int i = 0; i < 2; i++) {
			// 上
			DestoryWidthLine(
				m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + destory_line_range[i]
			);
		}
	}
}


void MapObjectFactory::CreateWidthLine(int create_line_y) {

	
	for (int x = 0; x < Map::MAX_IN_WINDOW_CHIP_NUM_W; x++) {

		// 配列外アクセスは許させない
		if (create_line_y < 0 || create_line_y > m_p_map->GetMaxHeightMapSize() || x < 0) {
			return;
		}

		// 位置を代入
		D3DXVECTOR2 pos(
			(float)(Map::CHIP_SIZE * x),
			(Map::CHIP_SIZE * -create_line_y) + Window::HEIGHT - m_p_map->GetPos().y
		);

		Texture::Draw2D("Resource/Texture/Map/chip-map_image_3.png", pos.x, pos.y -64.f);

		// チップが活動中なら生成中止
		if (m_p_map->IsActiveChipSelect(create_line_y, x) == true) {
			continue;
		}

		// 敵生成
		EnemyCreate(x, create_line_y);
		// 岩生成
		RockChipCreate(x, create_line_y);
	}
}


void MapObjectFactory::DestoryWidthLine(int destory_line_y) {

	// 下から線を作成
	int destory_line = m_p_map->GetMaxHeightMapSize() - destory_line_y;

	// 生成部分(下から生成していく)
	for (int x = 0; x < Map::MAX_IN_WINDOW_CHIP_NUM_W; x++) {

		// 位置を代入
		D3DXVECTOR2 pos(
			(float)(Map::CHIP_SIZE * x),
			(Map::CHIP_SIZE * -destory_line_y) + Window::HEIGHT - m_p_map->GetPos().y
		);

		//Texture::Draw2D("Resource/Texture/Map/chip-map_image_10.png", pos.x, pos.y);

		// チップ番号をMapクラスから受け取る
		bool is_active = m_p_map->IsActiveChipSelect(destory_line,x);

		// 配列外アクセスは許させない
		if (destory_line < 0 || destory_line > m_p_map->GetMaxHeightMapSize() || x < 0) {
			return;
		}

		// チップが活動しているなら
		if (is_active == true) {
		
			// マップチップ活動中止にする
			//is_active = false;
			m_p_map->ActiveChangeChipSelect(destory_line,x);
		}
	}
}


void MapObjectFactory::EnemyCreate(int x, int y) {

	// チップ座標位置を作成
	D3DXVECTOR2 pos(
		(float)(Map::CHIP_SIZE * x),
		(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_p_map->GetPos().y);

	// 修正値
	D3DXVECTOR2 fix_pos(0.f, -148.f);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_p_map->GetMaxHeightMapSize() - y;

	// チップ番号をMapクラスから受け取る
	int chip_num = m_p_map->GetChipNumChipSelect(create_chip_y,x);

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(create_chip_y,x) != false) {
		return;
	}

	// 敵生成チップ番号
	int enemy_chip[3] = { 100,101,102};
	// 敵の種類
	EnemyType enemy_type[3] = { SEAURCHIN ,NO_MOVE_SEAURCHIN , SELLFISH };

	// オブジェクト生成、チップ番号が100以上なら
	if (chip_num >= 100 &&
		chip_num <= 103) {
		
		for (int i = 0; i < 3; i++) {

			if (chip_num == enemy_chip[i]) {
				// 敵生成
				m_p_enemy_mng->CreateEnemy(pos + fix_pos, m_p_map, m_p_player[0], m_p_player[1],enemy_type[i]);
				// マップチップ記録
				m_p_map->ActiveChangeChipSelect(create_chip_y, x);
				break;
			}
		}

		if (chip_num == 103) {
			fix_pos.x += (float)Map::CHIP_SIZE + 600.f;
			// ブラインド生成
			m_p_enemy_mng->CreateBlind(pos + fix_pos, D3DXVECTOR2(-300.f,1000.f));
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(create_chip_y, x);
		}

	}
}


void MapObjectFactory::RockChipCreate(int x, int y) {

	// チップ座標位置を作成
	D3DXVECTOR2 pos(
		(float)(Map::CHIP_SIZE * x),
		(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_p_map->GetPos().y
	);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_p_map->GetMaxHeightMapSize() - y;

	// チップ番号をMapクラスから受け取る
	int chip_num = m_p_map->GetChipNumChipSelect(create_chip_y,x);

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(create_chip_y, x) != false) {
		return;
	}

	// 岩盤 HACK 作成中
	if (chip_num != 0 && chip_num <= 10) {

		// 位置を補正
		pos.y -= 64.f;

		// マップチップリスト追加
		m_rock_chip_list.push_back(
			new RockChip(
				chip_num,
				pos,
				m_p_map
			)
		);

		// 岩盤登録
		m_p_obj_mng->Entry(m_rock_chip_list.back());

		// マップチップ記録
		m_p_map->ActiveChangeChipSelect(create_chip_y, x);
	}
}
