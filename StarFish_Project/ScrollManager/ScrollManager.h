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
	* @brief 最大スクロールかどうか
	* @return bool
	*/
	bool IsScrollMax()const;


private:


	/**
	* @brief スクロール
	*/
	void Scroll();


	/**
	* @brief 最大スクロール
	*/
	void ScrollMax();


	/**
	* @brief スクリーン位置を戻す
	*/
	void ReturnScreenPos();


	/**
	* @brief スクロールを止める
	* @return bool 止めるならtrue止めないならfalseを返す
	*/
	bool StopScroll();


	/**
	* @brief スクロールできるかどうかを返す
	* @return bool
	*/
	bool IsScroll();


	/**
	* @brief 上スクロール範囲に入っているかどうか
	* @return 範囲に入っていたらtrue,入っていなかったらfalseを返す
	*/
	bool IsItInUpScrollScope(int i);


	/**
	* @brief 下スクロール範囲に入っているかどうか
	* @return 範囲に入っていたらtrue,入っていなかったらfalseを返す
	*/
	bool IsItInDownScrollScope(int i);

private:

	//! 最大スクロールか
	bool m_is_scroll_max;

	//! スクロールできるかどうか
	bool m_is_scroll;

	//! 自機配列
	PlayerManager * m_p_player_manager;

	//! マップ管理者のポインタ
	MapManager * m_p_map_manager;
};