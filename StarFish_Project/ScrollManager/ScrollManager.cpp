#include"ScrollManager.h"
#include"../Map/BackGround/BackGround.h"



ScrollManager::ScrollManager(PlayerManager*player_manager, MapManager*map_manager) : 
m_is_scroll(true),
m_is_scroll_max(false)
{

	// nullチェック
	if (player_manager == nullptr) {
		return;
	}

	if (map_manager == nullptr) {
		return;
	}

	// インスタンス代入
	m_p_player_manager = player_manager;
	m_p_map_manager = map_manager;
};


void ScrollManager::Update() {


	// スクロール範囲に入ったらスクリーン位置を戻す
	ReturnScreenPos();

	// スクロールを止めるかどうかのチェック
	/*if (StopScroll() == true) {
		return;
	}*/

	// スクロール
	if (m_is_scroll == true) {
		Scroll();
	}

	// スクロールの最大
	ScrollMax();
}


void ScrollManager::ReturnScreenPos() {

	for (int i = 0; i < Player::ID_TYPE::MAX_TYPE; i++) {

		// 上のスクロール範囲に入ったら
		if (IsItInUpScrollScope(i) == true) {

			// スクリーン座標を戻す
			m_p_player_manager->GetPlayerInstance(i)->SetPos(
				D3DXVECTOR2(m_p_player_manager->GetPlayerInstance(i)->GetPos().x,
					m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY()
				)
			);
		}

		// 下のスクロール範囲に入ったら
		else if (IsItInDownScrollScope(i) == true) {

			// スクリーン座標を戻す
			m_p_player_manager->GetPlayerInstance(i)->SetPos(
				D3DXVECTOR2(m_p_player_manager->GetPlayerInstance(i)->GetPos().x,
					m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY()
				)
			);
		}
	}
}


void ScrollManager::Scroll() {

	/* 上のスクロールを優先させる */

	for (int i = 0; i < Player::ID_TYPE::MAX_TYPE; i++) {

		// 上のスクロール範囲に入ったら
		if (IsItInUpScrollScope(i) == true) {

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollMove(
				m_p_player_manager->GetPlayerInstance(i)->GetMove().y
			);
			return;
		}
	}

	for (int i = 0; i < Player::ID_TYPE::MAX_TYPE; i++) {
		// 下のスクロール範囲に入ったら
		if (IsItInDownScrollScope(i) == true) {

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollMove(
				m_p_player_manager->GetPlayerInstance(i)->GetMove().y
			);
			return;
		}
	}
}



bool ScrollManager::IsItInUpScrollScope(int i) {

	// 上のスクロール範囲に入ったら
	if (m_p_player_manager->GetPlayerInstance(i)->GetPos().y <=
		m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY()) {
		return true;
	}
	return false;
}


bool ScrollManager::IsItInDownScrollScope(int i) {

	// 下のスクロール範囲に入ったら
	if (m_p_player_manager->GetPlayerInstance(i)->GetPos().y >=
		m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY()) {
		return true;
	}
	return false;
}


void ScrollManager::ScrollMax() {

	// 上の最大スクロール
	if (m_p_map_manager->GetMapInstance()->GetPos() <= -BackGround::MAX_UP_SCROLL + 1.f) {

		// 上のマップスクロール線初期化
		m_p_map_manager->GetMapInstance()->SetScrollUpLine(0.f);

		// スクロール移動初期化
		m_p_map_manager->GetMapInstance()->SetScrollMove(0.f);

		// マップ座標初期化
		m_p_map_manager->GetMapInstance()->SetPos(-BackGround::MAX_UP_SCROLL - 1.f);

		// 最大スクロールにする
		m_is_scroll_max = true;
	}
	else if (-m_p_map_manager->GetMapInstance()->GetPos() <= -BackGround::MAX_UP_SCROLL - 50.f) {
		// 元のスクロール座標に戻す
		m_p_map_manager->GetMapInstance()->SetScrollUpLine(Map::INIT_SCROLL_RANGE_UP);

		//m_is_max_scroll = false;
	}

	// 下の最大スクロール(移動値を加算する)
	if (m_p_map_manager->GetMapInstance()->GetPos() + -m_p_map_manager->GetMapInstance()->GetMove() > 0.f) {

		// マップ座標初期化
		m_p_map_manager->GetMapInstance()->SetPos(0.f);

		// スクロール移動初期化
		m_p_map_manager->GetMapInstance()->SetScrollMove(0.f);

	}
	else {
		// スクロールを最初に戻す
		m_p_map_manager->GetMapInstance()->SetScrollDownLine(Map::INIT_SCROLL_RANGE_DOWN);
	}
}


bool ScrollManager::StopScroll() {

	// 止める間隔
	const int STOP_POS_INTERVAL = 10;
	// 自機の移動値
	float player_get_pos_y = 0.f;

	// スクロールする上の範囲
	float map_scroll_scope_up = m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY() + STOP_POS_INTERVAL;
	// スクロールする下の範囲
	float map_scroll_scope_down = m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY() - STOP_POS_INTERVAL;

	// スクロール衝突情報受け取り
	CollisionDirectionType map_collision_dir_type =
		m_p_map_manager->GetMapInstance()->GetMapColliderInstance()->GetScrollCollisionDirType();

	// もう一つの自機の位置
	float one_player_pos_y = 0.f;

	for (int i = 0; i < Player::MAX_TYPE; i++) {

		// 自機の移動値受け取り
		player_get_pos_y = m_p_player_manager->GetPlayerInstance(i)->GetPos().y;

		// もう一つの自機受け取り
		one_player_pos_y = m_p_player_manager->GetPlayerInstance((i + 1) % 2)->GetPos().y;

		// 自機の衝突方向受け取り
		CollisionDirectionType player_collision_dir_type =
			m_p_player_manager->GetPlayerCollisionDirectionType(
			(Player::ID_TYPE)(i),
				HEIGHT
			);

		// スクロール範囲に入っており、かつチップに衝突している場合スクロール停止

		// スクリーン上の衝突
		if (player_collision_dir_type == UP &&
			player_get_pos_y >= map_scroll_scope_down
			||
			// スクロールの衝突
			map_collision_dir_type == UP &&
			player_get_pos_y >= map_scroll_scope_down
			) {

			// スクロールを止める
			m_is_scroll = false;
			return true;
		}
		// 衝突していなくて、スクロール範囲外に出ている時、スクロール開始
		else if (player_collision_dir_type == NONE &&
			player_get_pos_y > map_scroll_scope_down) {

			m_is_scroll = true;
		}

		// スクロール範囲に入っており、かつチップに衝突している場合スクロール停止
		// そしてもう一体の自機が下のスクロール範囲に入っている場合

		// スクリーン上の衝突
		if (player_collision_dir_type == DOWN &&
			player_get_pos_y <= map_scroll_scope_up &&
			one_player_pos_y >= map_scroll_scope_down
			||
			// スクロール上の衝突
			player_collision_dir_type == DOWN &&
			player_get_pos_y <= map_scroll_scope_up &&
			one_player_pos_y >= map_scroll_scope_down
			) {
			// スクロールを止める
			m_is_scroll = false;
			return true;
		}
		// 衝突していなくて、スクロール範囲外に出ている時、スクロール開始
		else if (player_collision_dir_type == NONE &&
			player_get_pos_y >= map_scroll_scope_up) {

			m_is_scroll = true;
		}
	}

	// スクロールを止める必要はなし
	return false;
}




bool ScrollManager::IsScrollMax()const{
	return m_is_scroll_max;
}


bool ScrollManager::IsScroll() {
	return m_is_scroll;
}
