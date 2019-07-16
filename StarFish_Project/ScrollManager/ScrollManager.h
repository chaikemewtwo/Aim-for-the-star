#pragma once
#include"../Player/PlayerManager.h"
#include"../Map/MapManager/MapManager.h"
#include"../ManagerBase/ManagerBase.h"



class ScrollManager : public ManagerBase{
public:


	/**
	* @brief コンストラクタ
	* @param[out] player1 自機１
	* @param[out] player2 自機２
	* @param[out] map マップ管理者
	*/
	ScrollManager(PlayerManager*player_manager,MapManager*map);


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


	/**
	* @brief 最大スクロールかどうか
	* @return bool
	*/
	bool IsMaxScroll()const;


private:

	//! 最大スクロールか
	bool m_is_max_scroll;

	//! 自機配列
	PlayerManager * m_p_player_manager;

	//! マップ管理者のポインタ
	MapManager * m_p_map_manager;
};