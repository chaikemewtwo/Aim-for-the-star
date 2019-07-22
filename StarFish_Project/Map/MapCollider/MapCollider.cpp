#include"MapCollider.h"
#include"../Map/Map.h"



MapCollider::MapCollider(Map*map) {

	// nullチェック
	if (map == nullptr) {
		return;
	}

	// マップインスタンス受け取り
	m_p_map = map;

	// スクロール方向初期化
	m_scroll_dir_y_type = NONE;
}


void MapCollider::Collision(
	D3DXVECTOR2&pos, 
	D3DXVECTOR2&move, 
	CollisionDirectionType &collision_dir_type_x, 
	CollisionDirectionType &collision_dir_type_y) 
{
	// サイズを修正
	const float RESIZE = 1.f;

	// 当たっているかどうか
	bool is_collision = false;

	// 四隅を作る
	D3DXVECTOR2 up_left(
		pos.x + RESIZE + CHIP_SCALE_X,
		pos.y + RESIZE + CHIP_SCALE_Y
	);

	D3DXVECTOR2 up_right(
		pos.x + Map::CHIP_SIZE - RESIZE - CHIP_SCALE_X,
		pos.y + RESIZE + CHIP_SCALE_Y
	);

	D3DXVECTOR2 down_left(
		pos.x + RESIZE + CHIP_SCALE_X,
		pos.y + Map::CHIP_SIZE - RESIZE - CHIP_SCALE_Y
	);

	D3DXVECTOR2 down_right(
		pos.x + Map::CHIP_SIZE - RESIZE - CHIP_SCALE_X,
		pos.y + Map::CHIP_SIZE - RESIZE - CHIP_SCALE_Y
	);


	YVertexHitCheck(
		up_left,
		up_right,
		down_left,
		down_right,
		pos,
		move.y,
		collision_dir_type_y
	);

	// y軸更新
	{
		up_left.y = pos.y + RESIZE + CHIP_SCALE_Y;
		up_right.y = pos.y + RESIZE + CHIP_SCALE_Y;
		down_left.y = pos.y + Map::CHIP_SIZE - RESIZE - CHIP_SCALE_Y;
		down_right.y = pos.y + Map::CHIP_SIZE - RESIZE - CHIP_SCALE_Y;
	}

	XVertexHitCheck(
		up_left,
		up_right,
		down_left,
		down_right,
		pos,
		move.x,
		collision_dir_type_x
	);

}


bool MapCollider::YVertexHitCheck(
	D3DXVECTOR2 up_left,
	D3DXVECTOR2 up_right,
	D3DXVECTOR2 down_left,
	D3DXVECTOR2 down_right,
	D3DXVECTOR2&pos,
	float&move_y,
	CollisionDirectionType &collision_dir_type_y
) {
	

	/* ---Y座標当たり判定--- */
	{

		// 衝突しているかどうかを調べるbool型
		bool is_collision = false;

		// y座標の衝突情報
		float collision_info_y[4][4] = {
		{ up_left.x,up_left.y,0.f,move_y },
		{ up_right.x,up_right.y,0.f,move_y },
		{ down_left.x,down_left.y + Map::CHIP_SIZE,0.f,move_y },
		{ down_right.x,down_right.y + Map::CHIP_SIZE,0.f,move_y },
		};

		// 過去の衝突情報取得
		CollisionDirectionType prev_dir_type_y = collision_dir_type_y;


		// y軸の衝突判定(四隅)
		for (int i = 0; i < 4; i++) {
			if (IsWallCollision(
				collision_info_y[i][0], collision_info_y[i][1],
				collision_info_y[i][2], collision_info_y[i][3]) == true) {

				// 衝突方向受け取り
				if (move_y != 0.f){
					collision_dir_type_y = GetCollisionDirectionSerchY(move_y);
				}

				// スクロール方向衝突方向受け取り
				m_scroll_dir_y_type = GetCollisionDirectionSerchY(-m_p_map->GetMove());

				// 縦の衝突判定
				HeightPosPullBackPrevPos(pos.y, move_y, collision_dir_type_y);

				// 衝突している
				is_collision = true;
			}
		}

		// 衝突していないなら
		if(is_collision != true){

			collision_dir_type_y = NONE;
		}

		return is_collision;
	}

	// 衝突していない
	return false;
}


bool MapCollider::XVertexHitCheck(
	D3DXVECTOR2 up_left,
	D3DXVECTOR2 up_right,
	D3DXVECTOR2 down_left,
	D3DXVECTOR2 down_right,
	D3DXVECTOR2&pos,
	float&move_x,
	CollisionDirectionType &collision_dir_type_x
){

	/* ---X座標当たり判定--- */
	{
		// 衝突しているかどうかを調べるbool型
		bool is_collision = false;

		// 衝突情報x座標
		float collision_info_x[6][4] = {
		{ up_left.x,up_left.y,move_x,0.f },
		{ up_right.x,up_right.y,move_x,0.f },
		{ down_left.x,down_left.y + Map::CHIP_SIZE,move_x,0.f },
		{ down_right.x,down_right.y + Map::CHIP_SIZE,move_x,0.f },
		{ down_left.x, down_right.y, move_x, 0.f },
		{ down_right.x, down_right.y, move_x, 0.f },
		};


		for (int i = 0; i < 6; i++) {
			if (IsWallCollision(
				collision_info_x[i][0], collision_info_x[i][1],
				collision_info_x[i][2], collision_info_x[i][3]) == true) {

				// 衝突方向受け取り
				collision_dir_type_x = GetCollisionDirectionSerchX(move_x);

				// 横方向の位置を受け取り、その分引き戻す
				WidthPosPullBackToPrevPos(pos.x, move_x, collision_dir_type_x);

				// 衝突した
				is_collision = true;
			}
		}

		// 衝突していないなら衝突方向をNONEにする
		if (is_collision != true) {

			collision_dir_type_x = NONE;
		}

		return is_collision;
	}

	return false;
}


bool MapCollider::IsWallCollision(float pos_x, float pos_y, float move_x, float move_y) {

	// 当たり位置0.f
	float hit_pos_y = 0.f;

	{
		// スクロールしているなら、スクロール移動値加算
		if (-m_p_map->GetMove() != 0.f) {

			hit_pos_y = pos_y + (m_p_map->GetPos()) + -m_p_map->GetMove();
		}
		// スクロールしていないなら、スクリーン移動値加算
		else{
			hit_pos_y = pos_y + (m_p_map->GetPos()) + move_y;
		}
	}

	// 現在のスクリーン座標にマップ座標を加算する
	D3DXVECTOR2 after_pos(pos_x + move_x,hit_pos_y);

	// 床と衝突しているか(障害物は50番号まで),0番号は何もなし
	if (m_p_map->GetChipParam(after_pos.x, after_pos.y) <= 50 && m_p_map->GetChipParam(after_pos.x, after_pos.y) >= 1) {

		// 衝突している
		return true;
	}
	// 衝突していない
	return false;
}


void MapCollider::HeightPosPullBackPrevPos(float &pos_y, float &move_y, CollisionDirectionType &collision_dir_type_y) {


	// 入ったマップチップの座標を割り出す
	float chip_pos_y = 0.f;

	float get_move = 0.f;

	if (m_p_map->GetMove() != 0.f) {
		get_move = m_p_map->GetMove();
	}
	if (move_y != 0.f) {
		get_move = move_y + 2.f;
	}

	// 上の衝突、スクリーン内の移動値とスクロール移動値による
	if (collision_dir_type_y == UP || m_scroll_dir_y_type == UP) {

		// チップサイズ割り出し
		chip_pos_y = (float)m_p_map->GetChipCastByPos((pos_y + (m_p_map->GetPos())) + 1);

		// 下に戻す
		pos_y = (chip_pos_y * Map::CHIP_SIZE) + ((-m_p_map->GetPos()) + get_move);

		// 拡縮Y
		if (CHIP_SCALE_Y > 0.f) {
			// 修正(自機の移動とマップの移動を加算)
			pos_y += (Map::CHIP_SIZE - CHIP_SCALE_Y);
		}

		// 移動ベクトルなし
		move_y = 0.f;
	}

	
	// 下の衝突、スクリーン内の移動値による
	else if (collision_dir_type_y == DOWN) {

		// チップサイズ割り出し
		chip_pos_y = (float)m_p_map->GetChipCastByPos((pos_y + m_p_map->GetPos()));

		// 上に戻す
		pos_y = (chip_pos_y * Map::CHIP_SIZE) + (-m_p_map->GetPos()) + get_move;

		// 衝突後の移動分減算
		pos_y += -move_y - m_p_map->GetMove();

		// サイズY
		if (CHIP_SCALE_Y > 0.f) {
			// 修正
			pos_y += CHIP_SCALE_Y;
		}


		// 移動ベクトルなし
		move_y = 0.f;
	}
}


// 横マップの位置に修正
void MapCollider::WidthPosPullBackToPrevPos(float &pos_x, float &move_x, CollisionDirectionType &collision_dir_type_x) {


	// 入ったマップチップの座標を割り出す
	float chip_pos_x = 0;

	// 左
	if (collision_dir_type_x == LEFT) {

		// チップに変換
		chip_pos_x = (float)m_p_map->GetChipCastByPos(pos_x);

		// X位置を右に戻す
		pos_x = (chip_pos_x * Map::CHIP_SIZE) - move_x;

		// 縮小する時
		if (CHIP_SCALE_X > 0.f) {
			pos_x += (Map::CHIP_SIZE - CHIP_SCALE_X);
		}

		// 移動ベクトルなし
		move_x = 0.f;
	}

	// 右
	else if (collision_dir_type_x == RIGHT) {

		chip_pos_x = (float)m_p_map->GetChipCastByPos(pos_x);
		// 位置を戻す
		pos_x = (chip_pos_x * Map::CHIP_SIZE) - move_x;

		if (CHIP_SCALE_X > 0.f) {
			pos_x += CHIP_SCALE_X;
		}

		// 移動ベクトルなし
		move_x = 0.f;
	}
}


CollisionDirectionType MapCollider::GetCollisionDirectionSerchX(const float&move_x)const {

	// 左右の衝突方向を調べる

	// 右に衝突した場合
	if (move_x > 0.f) {
		return RIGHT;
	}
	// 左に衝突した場合
	else if (move_x < 0.f) {
		return LEFT;
	}

	return NONE;
}


CollisionDirectionType MapCollider::GetCollisionDirectionSerchY(const float&move_y)const {

	// 縦の衝突方向を調べる

	// 下に衝突した場合
	if (move_y > 0.f) {
		return DOWN;
	}
	// 上に衝突した場合
	else if (move_y < 0.f) {
		return UP;
	}

	return NONE;
}


CollisionDirectionType MapCollider::GetScrollCollisionDirType() {
	return m_scroll_dir_y_type;
}
