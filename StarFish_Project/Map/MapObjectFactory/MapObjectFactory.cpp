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


void MapObjectFactory::Update() {


	// 生成
	{
		Create(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + 18
		);

		Create(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y)
		);
	}

	// 削除
	{
		Destory(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + 18 + 1
		);

		Destory(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + 5
		);
	}
}


void MapObjectFactory::Create(int create_line_y) {

	// y軸の線を作成
	create_line_y = (m_p_map->GetMaxHeightMapSize()) - create_line_y;

	for (int x = 0; x < 30 - 1; x++) {

		// 配列外アクセスは許させない
		if (create_line_y < 0 || x < 0) {
			return;
		}

		// 位置を代入
		D3DXVECTOR2 pos((float)(Map::CHIP_SIZE * x), (Map::CHIP_SIZE * -create_line_y) + Window::HEIGHT - m_p_map->GetPos().y);

		//Texture::Draw2D("Resource/Texture/Map/chip-map_image_3.png", pos.x, (float)CHIP_SIZE * -create_line[0] + Window::HEIGHT - m_pos.y);
		//Texture::Draw2D("Resource/Texture/Map/chip-map_image_4.png", pos.x, (float)CHIP_SIZE * -create_line[1] + Window::HEIGHT - m_pos.y);

		// 敵生成
		EnemyCreate(x,create_line_y);
		// 岩生成
		RockChipCreate(x,create_line_y);
	}
}


void MapObjectFactory::Destory(int destory_line_y) {

	// 下から線を作成
	destory_line_y = m_p_map->GetMaxHeightMapSize() - destory_line_y;

	// 生成部分(下から生成していく)
	for (int x = 0; x < 30 - 1; x++) {

		// チップ番号をMapクラスから受け取る
		bool is_active = m_p_map->IsActiveChipSelect(x, destory_line_y);

		// 配列外アクセスは許させない
		if (m_p_map->GetMaxHeightMapSize() + destory_line_y < 0 || x < 0) {
			return;
		}

		// チップが活動しているなら
		if (is_active == true) {
			// マップチップ活動中にする
			//is_active = false;
			m_p_map->ActiveChangeChipSelect(x, destory_line_y);
		}
	}
}


void MapObjectFactory::EnemyCreate(int x, int y) {


	// 位置を代入
	D3DXVECTOR2 pos((float)(Map::CHIP_SIZE * x),(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_p_map->GetPos().y);
	// 修正値
	D3DXVECTOR2 fix_pos(0.f, -148.f);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_p_map->GetMaxHeightMapSize() - y;
	// チップ番号をMapクラスから受け取る
	int chip_num = m_p_map->GetChipNumChipSelect(create_chip_y, x);

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(x, y) != false) {
		return;
	}

	// オブジェクト生成、チップ番号が100以上なら
	if (chip_num >= 100 &&
		chip_num <= 104) {
		switch (chip_num) {
			// ウニ生成
		case 100:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], SEAURCHIN);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(x, y);
			break;
			// 落ちていくウニ生成
		case 101:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], NO_MOVE_SEAURCHIN);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(x, y);
			break;
			// 貝生成
		case 102:
			// 補正
			fix_pos.x += Map::CHIP_SIZE - 12.f;
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], SELLFISH);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(x, y);
			break;
			// 右下に行くブラインド生成
		case 103:
			fix_pos.x += (float)Map::CHIP_SIZE + 600.f;
			// ブラインド生成
			m_p_enemy_mng->CreateBlind(pos + fix_pos, D3DXVECTOR2(-100.f, 1000.f));
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(x, y);
			break;
		}
	}
}


void MapObjectFactory::RockChipCreate(int x, int y) {

	// チップ座標位置を作成
	D3DXVECTOR2 pos((float)(Map::CHIP_SIZE * x), (Map::CHIP_SIZE * -y) + Window::HEIGHT - m_p_map->GetPos().y);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_p_map->GetMaxHeightMapSize() - y;
	// チップ番号をMapクラスから受け取る
	int chip_num = m_p_map->GetChipNumChipSelect(create_chip_y, x);

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(x, y) != false) {
		return;
	}

	// 岩盤 HACK 作成中
	if (chip_num != 0 && chip_num <= 10) {

		// 位置を補正
		pos.y -= 64.f;
		// 岩盤生成
		m_p_obj_mng->Entry(
			new BedRockChip(
				chip_num,
				pos,
				m_p_map
			)
		);
		// マップチップ記録
		m_p_map->ActiveChangeChipSelect(x, y);
	}
}
