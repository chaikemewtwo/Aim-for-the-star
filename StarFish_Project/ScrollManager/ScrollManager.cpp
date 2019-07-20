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
	if (StopScroll() == true) {
		return;
	}

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

	for (int i = 0; i < Player::ID_TYPE::MAX_TYPE; i++) {
		
		// 上のスクロール範囲に入ったら
		if (IsItInUpScrollScope(i) == true) {

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollMove(
				m_p_player_manager->GetPlayerInstance(i)->GetMove().y
			);
		}

		// 下のスクロール範囲に入ったら
		else if (IsItInDownScrollScope(i) == true) {

			// マップ移動を加算
			m_p_map_manager->GetMapInstance()->SetScrollMove(
				m_p_player_manager->GetPlayerInstance(i)->GetMove().y
			);
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

	const int STOP_POS_INTERVAL = 100;

	for (int i = 0; i < Player::MAX_TYPE; i++){

		
		// スクロール範囲に入っており、かつチップに衝突している場合スクロール停止
		if (m_p_player_manager->GetPlayerCollisionDirectionType(
			(Player::ID_TYPE)(i), HEIGHT) == UP &&

			m_p_player_manager->GetPlayerInstance(i)->GetPos().y >=
			m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY() - STOP_POS_INTERVAL
			){
			// Y位置を戻す
			m_p_player_manager->GetPlayerInstance(i)->SetPos(
				D3DXVECTOR2(
					m_p_player_manager->GetPlayerInstance(i)->GetPos().x,
					m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY() - STOP_POS_INTERVAL)
			);

			// スクロールを止める
			m_is_scroll = false;
			return true;
		}
		// 衝突していなくて、スクロール範囲外に出ている時、スクロール開始
		else if(m_p_player_manager->GetPlayerInstance(i)->GetPos().y >
			m_p_map_manager->GetMapInstance()->GetScrollDownMapPosY() - STOP_POS_INTERVAL){
			m_is_scroll = true;
		}

		// スクロール範囲に入っており、かつチップに衝突している場合スクロール停止
		if (m_p_player_manager->GetPlayerCollisionDirectionType(
			(Player::ID_TYPE)(i), HEIGHT) == DOWN &&

			m_p_player_manager->GetPlayerInstance(i)->GetPos().y <=
			m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY() + STOP_POS_INTERVAL
			) {

			// Y位置を戻す
			m_p_player_manager->GetPlayerInstance(i)->SetPos(
				D3DXVECTOR2(
					m_p_player_manager->GetPlayerInstance(i)->GetPos().x,
					m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY() + STOP_POS_INTERVAL)
			);

			// スクロールを止める
			m_is_scroll = false;
			return true;
		}
		// 衝突していなくて、スクロール範囲外に出ている時、スクロール開始
		else if(m_p_player_manager->GetPlayerInstance(i)->GetPos().y >=
			m_p_map_manager->GetMapInstance()->GetScrollUpMapPosY() + STOP_POS_INTERVAL){
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
