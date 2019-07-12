#pragma once
#include"../../Player/Player.h"
#include"../Map/MapManager/MapManager.h"



class ScrollManager {
public:


	/**
	* @brief コンストラクタ
	* @param[out] player1 自機１
	* @param[out] player2 自機２
	* @param[out] map マップ管理者
	*/
	ScrollManager(Player*player1, Player*player2, MapManager*map);


	/**
	* @brief 更新
	*/
	void Update();


	/**
	* @brief スクロール
	*/
	void Scroll();


	/**
	* @brief 最大スクロール
	*/
	void MaxScroll();


private:

	//! 自機配列
	Player * m_p_player_list[Player::MAX];

	//! マップ管理者のポインタ
	MapManager * m_p_map_manager;
};