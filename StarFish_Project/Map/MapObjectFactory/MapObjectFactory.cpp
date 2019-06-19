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
		// 上
		Create(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + CREATE_LINE_UP
		);
	
		// 下
		Create(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + CREATE_LINE_DOWN
		);
	}
	
	// 削除
	{
		// 上
		Destory(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + DESTORY_LINE_UP
		);
	
		// 下
		Destory(
			m_p_map->GetChipCastByPos(-m_p_map->GetPos().y) + DESTORY_LINE_DOWN
		);
	}
}


void MapObjectFactory::Create(int create_line_y) {

	// y軸の線を作成
	int create_line = (m_p_map->GetMaxHeightMapSize()) - create_line_y;

	for (int x = 0; x < Map::MAX_CHIP_NUM_W; x++) {

		// 配列外アクセスは許させない
		if (create_line_y < 0 || create_line_y > m_p_map->GetMaxHeightMapSize() || x < 0) {
			return;
		}

		// 位置を代入
		D3DXVECTOR2 pos(
			(float)(Map::CHIP_SIZE * x),
			(Map::CHIP_SIZE * -create_line_y) + Window::HEIGHT - m_p_map->GetPos().y
		);

		Texture::Draw2D("Resource/Texture/Map/chip-map_image_3.png", pos.x, pos.y);

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


void MapObjectFactory::Destory(int destory_line_y) {

	// 下から線を作成
	int destory_line = m_p_map->GetMaxHeightMapSize() - destory_line_y;

	// 生成部分(下から生成していく)
	for (int x = 0; x < Map::MAX_CHIP_NUM_W; x++) {

		// 位置を代入
		//D3DXVECTOR2 pos(
		//	(float)(Map::CHIP_SIZE * x),
		//	(Map::CHIP_SIZE * -destory_line_y) + Window::HEIGHT - m_p_map->GetPos().y
		//);

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


	// 位置を代入
	D3DXVECTOR2 pos((float)(Map::CHIP_SIZE * x),(Map::CHIP_SIZE * -y) + Window::HEIGHT - m_p_map->GetPos().y);
	// 修正値
	D3DXVECTOR2 fix_pos(0.f, -148.f);

	// Mapの高さから今のyチップ座標を割り出し
	int create_chip_y = m_p_map->GetMaxHeightMapSize() - y;

	// チップ番号をMapクラスから受け取る
	int chip_num = m_p_map->GetChipNumChipSelect(y,x);

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(y,x) != false) {
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
			m_p_map->ActiveChangeChipSelect(y,x);
			break;

			// 落ちていくウニ生成
		case 101:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], NO_MOVE_SEAURCHIN);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(y,x);
			break;

			// 貝生成
		case 102:
			// 敵生成
			m_p_enemy_mng->CreateEnemy(pos + fix_pos,m_p_map, m_p_player[0], m_p_player[1], SELLFISH);
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(y,x);
			break;

			// 右下に行くブラインド生成
		case 103:
			fix_pos.x += (float)Map::CHIP_SIZE + 600.f;
			// ブラインド生成
			m_p_enemy_mng->CreateBlind(pos + fix_pos, D3DXVECTOR2(-100.f, 1000.f));
			// マップチップ記録
			m_p_map->ActiveChangeChipSelect(y,x);
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
	int chip_num = m_p_map->GetChipNumChipSelect(y,x);

	// チップが活動中なら生成中止
	if (m_p_map->IsActiveChipSelect(y, x) != false) {
		return;
	}

	// 岩盤 HACK 作成中
	if (chip_num != 0 && chip_num <= 10) {

		// 位置を補正
		pos.y -= 64.f;

		// マップチップリスト追加
		m_rock_chip_list.push_back(
			new BedRockChip(
				chip_num,
				pos,
				m_p_map
			)
		);

		// 岩盤登録
		m_p_obj_mng->Entry(m_rock_chip_list.back());

		// マップチップ記録
		m_p_map->ActiveChangeChipSelect(y, x);
	}
}
