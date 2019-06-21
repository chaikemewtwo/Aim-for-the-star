#include"MapCollision.h"



MapCollision::MapCollision(Map*map) {
	m_p_map = map;
}


bool MapCollision::HitChack(D3DXVECTOR2&pos, D3DXVECTOR2&move) {

	const float Resize = 1.f;  // サイズを修正
	bool is_collision = false; // 当たっているかどうか

	// 左上
	D3DXVECTOR2 up_left(pos.x + Resize + CHIP_SCALE_X, pos.y + Resize + CHIP_SCALE_Y);
	// 右上
	D3DXVECTOR2 up_right(pos.x + Map::CHIP_SIZE - Resize - CHIP_SCALE_X, pos.y + Resize + CHIP_SCALE_Y);
	// 左下
	D3DXVECTOR2 down_left(pos.x + Resize + CHIP_SCALE_X, pos.y + Map::CHIP_SIZE - Resize - CHIP_SCALE_Y);
	// 右下
	D3DXVECTOR2 down_right(pos.x + Map::CHIP_SIZE - Resize - CHIP_SCALE_X, pos.y + Map::CHIP_SIZE - Resize - CHIP_SCALE_Y);

	float collision_info_y[4][4] = {
		{ up_left.x,up_left.y,0.f,move.y },
	{ up_right.x,up_right.y,0.f,move.y },
	{ down_left.x,down_left.y + Map::CHIP_SIZE,0.f,move.y },
	{ down_right.x,down_right.y + Map::CHIP_SIZE,0.f,move.y },
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
		SidePosFixToMapPos(pos.y, move.y);
		// 衝突していないに変更
		is_collision = false;
	}

	// y軸更新
	up_left.y = pos.y + Resize + CHIP_SCALE_Y;
	up_right.y = pos.y + Resize + CHIP_SCALE_Y;
	down_left.y = pos.y + Map::CHIP_SIZE - Resize - CHIP_SCALE_Y;
	down_right.y = pos.y + Map::CHIP_SIZE - Resize - CHIP_SCALE_Y;

	float collision_info_x[6][4] = {
		{ up_left.x,up_left.y,move.x,0.f },
	{ up_right.x,up_right.y,move.x,0.f },
	{ down_left.x,down_left.y + Map::CHIP_SIZE,move.x,0.f },
	{ down_right.x,down_right.y + Map::CHIP_SIZE,move.x,0.f },
	{ down_left.x, down_right.y, move.x, 0.f },
	{ down_right.x, down_right.y, move.x, 0.f },
	};

	for (int i = 0; i < 6; i++) {
		if (IsFloorCollision(collision_info_x[i][0], collision_info_x[i][1], collision_info_x[i][2], collision_info_x[i][3]) == true) {
			is_collision = true;
		}
	}
	if (is_collision == true) {
		is_collision = false;
		SidePosFixToMapPos(pos.x, move.x);
	}

	return is_collision;
}


void MapCollision::InitWallCollision() {

	// 衝突していない
	//m_is_wall_col[0] = false;
	//m_is_wall_col[1] = false;
	m_is_wall_collision_up = false;
	m_is_wall_collision_down = false;
	m_is_wall_collision_right = false;
	m_is_wall_collision_left = false;
}


bool MapCollision::IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y) {

	// 現在のスクリーン座標にマップ座標を加算する
	D3DXVECTOR2 after_pos(pos_x + move_x, pos_y + move_y + (m_p_map->GetPos().y) + m_p_map->GetMove().y);

	// 床と衝突しているか(障害物は50番号まで),0番号は何もなし
	if (m_p_map->GetChipParam(after_pos.x, after_pos.y) <= 50 && m_p_map->GetChipParam(after_pos.x, after_pos.y) >= 1) {

		// 衝突している
		return true;
	}
	// 衝突していない
	return false;
}


// 横マップの位置に修正
void MapCollision::SidePosFixToMapPos(float &pos_x, float &move_x) {


	// 入ったマップチップの座標を割り出す
	float chip_pos_x = 0;

	// 左
	if (move_x < 0.f) {

		// チップに変換
		chip_pos_x = (float)m_p_map->GetChipCastByPos(pos_x - (1));

		// X位置を右に戻す
		pos_x = (chip_pos_x * Map::CHIP_SIZE) - move_x;

		// 縮小する時
		if (CHIP_SCALE_X > 0.f) {
			pos_x += (Map::CHIP_SIZE - CHIP_SCALE_X);
		}

		// 移動ベクトルなし
		move_x = 0.f;
		// 左に衝突
		m_is_wall_collision_left = true;
	}

	// 右
	else if (move_x > 0.f) {

		chip_pos_x = (float)m_p_map->GetChipCastByPos(pos_x);
		// 位置を戻す
		pos_x = (chip_pos_x * Map::CHIP_SIZE) - move_x;

		if (CHIP_SCALE_X > 0.f) {
			pos_x += CHIP_SCALE_X;
		}

		// 移動ベクトルなし
		move_x = 0.f;
		// 右に衝突
		m_is_wall_collision_right = true;
	}
}


void MapCollision::VerticalPosFixToMapPos(float &pos_y, float &move_y) {

	// 入ったマップチップの座標を割り出す
	float chip_pos_y = 0.f;

	// 上(自機の移動とマップの移動が進んだ時)
	if (move_y < 0.f || m_p_map->GetMove().y < 0.f) {

		// チップサイズ割り出し
		chip_pos_y = (float)m_p_map->GetChipCastByPos((pos_y + (m_p_map->GetPos().y)) - (move_y - 1 + CHIP_SCALE_Y));

		// 下に戻す
		pos_y = (chip_pos_y * Map::CHIP_SIZE) + (-m_p_map->GetPos().y) - m_p_map->GetMove().y;

		// 当たりチップ
		if (CHIP_SCALE_Y > 0.f) {
			// 修正(自機の移動とマップの移動を加算)
			pos_y += (Map::CHIP_SIZE - CHIP_SCALE_Y);
		}
		
		// スクロール範囲に入っていれば
		if (pos_y < m_p_map->GetScrollRangeUp()) {
			// 位置を戻す
			D3DXVECTOR2 pos(m_p_map->GetPos().x,-m_p_map->GetPos().y);
			pos.y += (pos_y - m_p_map->GetScrollRangeUp());
			m_p_map->SetPos(pos);
		}

		// 移動ベクトルなし
		move_y = 0.f;
		// 上に衝突
		m_is_wall_collision_up = true;
	}

	// 下(自機の移動とマップの移動が進んだ時)
	else if (move_y > 0.f || m_p_map->GetMove().y > 0.f) {

		// チップサイズ割り出し
		chip_pos_y = (float)m_p_map->GetChipCastByPos((pos_y + m_p_map->GetPos().y) + move_y);

		// 上に戻す
		pos_y = (chip_pos_y * Map::CHIP_SIZE) + (-m_p_map->GetPos().y);
		pos_y += -move_y - m_p_map->GetMove().y;

		// サイズY
		if (CHIP_SCALE_Y > 0.f) {
			pos_y += CHIP_SCALE_Y;
		}

		// スクロール範囲に入っていれば
		if (pos_y > m_p_map->GetScrollRangeDown()) {

			// 位置を戻す
			D3DXVECTOR2 pos(m_p_map->GetPos().x, -m_p_map->GetPos().y);
			pos.y += (pos_y + m_p_map->GetScrollRangeDown());
			m_p_map->SetPos(pos);
		}

		// 移動ベクトルなし
		move_y = 0.f;
		// 下に衝突
		m_is_wall_collision_down = true;
	}
}


bool MapCollision::IsStand()const {
	return m_is_stand;
}

bool MapCollision::IsWallCollision()const {
	return m_is_wall_collision;
}

bool MapCollision::IsWallColUp()const {
	return m_is_wall_collision_up;
}

bool MapCollision::IsWallColDown()const {
	return m_is_wall_collision_down;
}

bool MapCollision::IsWallColLeft()const {
	return m_is_wall_collision_left;
}

bool MapCollision::IsWallColRight()const {
	return m_is_wall_collision_right;
}