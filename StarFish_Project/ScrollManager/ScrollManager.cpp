#include"ScrollManager.h"
#include"../Map/BackGround/BackGround.h"



ScrollManager::ScrollManager(Player*player1, Player*player2, MapManager*map) {
	
	// nullチェック
	if (player1 == nullptr) {
		return;
	}

	if (player2 == nullptr) {
		return;
	}

	if (map == nullptr) {
		return;
	}

	// インスタンス代入
	m_p_player_list[Player::STAR_1] = player1;
	m_p_player_list[Player::STAR_2] = player2;
	m_p_map_manager = map;

};


void ScrollManager::Update() {

	// スクロール
	Scroll();

	// 最大スクロール 
	MaxScroll();
}


void ScrollManager::Scroll() {

	for (int i = 0; i < Player::MAX; i++) {

		// 上のスクロール範囲に入ったら
		if (m_p_player_list[i]->GetPos().y <= m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY()) {

			// スクリーン座標を戻す
			m_p_player_list[i]->SetPos(D3DXVECTOR2(m_p_player_list[i]->GetPos().x, m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY()));

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollYMove(m_p_player_list[i]->GetMove().y);
		}

		// 下のスクロール範囲に入ったら
		else if (m_p_player_list[i]->GetPos().y >= m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY()) {

			// スクリーン座標を戻す
			m_p_player_list[i]->SetPos(D3DXVECTOR2(m_p_player_list[i]->GetPos().x, m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY()));

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollYMove(m_p_player_list[i]->GetMove().y);
		}
	}
}


void ScrollManager::MaxScroll() {

	// 上の最大スクロール
	if (-m_p_map_manager->GetMapInstance()->GetPos().y <= -BackGround::MAX_UP_SCROLL + 1.f) {

		// 上のマップスクロール線初期化
		m_p_map_manager->GetMapInstance()->SetScrollUpLine(0.f);

		// スクロール移動初期化
		m_p_map_manager->GetMapInstance()->SetScrollYMove(0.f);

		// マップ座標初期化
		m_p_map_manager->GetMapInstance()->SetPos(D3DXVECTOR2(m_p_map_manager->GetMapInstance()->GetPos().x ,-BackGround::MAX_UP_SCROLL - 1.f));

		// 最大スクロールにする
		m_p_map_manager->GetMapInstance()->SetIsScroll(true);
	}
	else if (-m_p_map_manager->GetMapInstance()->GetPos().y <= -BackGround::MAX_UP_SCROLL - 50.f) {
		// 元のスクロール座標に戻す
		m_p_map_manager->GetMapInstance()->SetScrollUpLine(Map::INIT_SCROLL_RANGE_UP);
	}

	// 下の最大スクロール
	if (m_p_map_manager->GetMapInstance()->GetPos().y > 0.f) {

		m_p_map_manager->GetMapInstance()->SetScrollDownLine(800.f);
	
		// スクロール移動初期化
		m_p_map_manager->GetMapInstance()->SetScrollYMove(0.f);

		// マップ座標初期化
		m_p_map_manager->GetMapInstance()->SetPos(D3DXVECTOR2(m_p_map_manager->GetMapInstance()->GetPos().x,0.f));
	}
	else {
		// スクロールを最初に戻す
		m_p_map_manager->GetMapInstance()->SetScrollDownLine(Map::INIT_SCROLL_RANGE_DOWN);
	}
}