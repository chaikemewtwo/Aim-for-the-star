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


void MapObjectFactory::Create(int create_line,int create_chip_x,int create_chip_y,int chip_num,bool *is_active) {


	// 生成部分(下から生成していく)
	for (int x = 0; x < 30; x++) {

		int create_chip_y = (m_p_map->GetMaxHeightMapSize()) - create_line;

		// 配列外アクセスは許させない
		if (create_chip_y < 0 || x < 0) {
			return;
		}

		// 位置を代入
		D3DXVECTOR2 pos((float)(Map::CHIP_SIZE * x), (Map::CHIP_SIZE * -create_line) + Window::HEIGHT - m_p_map->GetPos().y);

		//Texture::Draw2D("Resource/Texture/Map/chip-map_image_3.png", pos.x, (float)CHIP_SIZE * -create_line[0] + Window::HEIGHT - m_pos.y);
		//Texture::Draw2D("Resource/Texture/Map/chip-map_image_4.png", pos.x, (float)CHIP_SIZE * -create_line[1] + Window::HEIGHT - m_pos.y);

		// 敵生成
		EnemyCreate(x, create_line,chip_num);
		// 岩生成
		RockChipCreate(x, create_line,chip_num);
	}
}


void MapObjectFactory::Destory(int destory_line, int destory_chip_x, int destory_chip_y,bool *is_active) {

	// 生成部分(下から生成していく)
	for (int x = 0; x < 30; x++) {

		// 配列外アクセスは許させない
		if (m_p_map->GetMaxHeightMapSize() + destory_line < 0 || x < 0) {
			return;
		}

		// チップが活動しているなら
		if (*is_active == true) {
			// マップチップ活動中にする
			*is_active = false;
		}
	}
}


void MapObjectFactory::EnemyCreate(int x, int y, int chip_num) {

	// 位置を代入
	D3DXVECTOR2 pos((float)(Map::CHIP_SIZE * x),(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_p_map->GetPos().y);
	// 修正値
	D3DXVECTOR2 fix_pos(0.f, -148.f);

	int create_chip_y = m_p_map->GetMaxHeightMapSize() - y;

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(y, x) != false) {
		return;
	}

	// オブジェクト生成、チップ番号が100以上なら
	if (chip_num >= 100 && chip_num <= 104) {
		switch (chip_num) {
			// ウニ生成
		case 100:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], SEAURCHIN);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(y, x);
			break;
			// 落ちていくウニ生成
		case 101:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], NO_MOVE_SEAURCHIN);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(y, x);
			break;
			// 貝生成
		case 102:
			// 補正
			fix_pos.x += Map::CHIP_SIZE - 12.f;
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], SELLFISH);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(y, x);
			break;
			// 右下に行くブラインド生成
		case 103:
			fix_pos.x += (float)Map::CHIP_SIZE + 600.f;
			// ブラインド生成
			m_p_enemy_mng->CreateBlind(pos + fix_pos, D3DXVECTOR2(-100.f, 1000.f));
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(y, x);
			break;
		}
	}
}


void MapObjectFactory::RockChipCreate(int x, int y, int chip_num) {

	D3DXVECTOR2 pos((float)(Map::CHIP_SIZE * x), (Map::CHIP_SIZE * -y) + Window::HEIGHT - m_p_map->GetPos().y);
	int create_chip_y = m_p_map->GetMaxHeightMapSize() - y;

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(y, x) != false) {
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
		m_p_map->ActiveChangeChipSelect(y, x);
	}
}
