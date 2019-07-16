#include"ScrollManager.h"
#include"../Map/BackGround/BackGround.h"



ScrollManager::ScrollManager(PlayerManager*player_manager, MapManager*map) {

	// nullチェック
	if (player_manager == nullptr) {
		return;
	}

	if (map == nullptr) {
		return;
	}

	m_is_max_scroll = false;

	// インスタンス代入
	m_p_player_manager = player_manager;
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
		if (m_p_player_manager->GetPlayerInstance(i)->GetPos().y <= m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY()) {

			// スクリーン座標を戻す
			m_p_player_manager->GetPlayerInstance(i)->SetPos(
				D3DXVECTOR2(m_p_player_manager->GetPlayerInstance(i)->GetPos().x,
					m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY()
				)
			);

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollMove(
				m_p_player_manager->GetPlayerInstance(i)->GetMove().y
			);
		}

		// 下のスクロール範囲に入ったら
		else if (m_p_player_manager->GetPlayerInstance(i)->GetPos().y >=
			     m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY()) {

			// スクリーン座標を戻す
			m_p_player_manager->GetPlayerInstance(i)->SetPos(
				D3DXVECTOR2(m_p_player_manager->GetPlayerInstance(i)->GetPos().x,
					m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY()
				)
			);

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollMove(
				m_p_player_manager->GetPlayerInstance(i)->GetMove().y
			);
		}
	}
}


void ScrollManager::MaxScroll() {

	// 上の最大スクロール
	if (m_p_map_manager->GetMapInstance()->GetPos() <= -BackGround::MAX_UP_SCROLL + 1.f) {

		// 上のマップスクロール線初期化
		m_p_map_manager->GetMapInstance()->SetScrollUpLine(0.f);

		// スクロール移動初期化
		m_p_map_manager->GetMapInstance()->SetScrollMove(0.f);

		// マップ座標初期化
		m_p_map_manager->GetMapInstance()->SetPos(-BackGround::MAX_UP_SCROLL - 1.f);

		// 最大スクロールにする
		m_is_max_scroll = true;
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


bool ScrollManager::IsMaxScroll()const{
	return m_is_max_scroll;
}