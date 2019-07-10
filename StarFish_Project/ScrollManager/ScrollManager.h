#pragma once
#include"../Map/MapManager/MapManager.h"
#include"../Player/Player.h"



class ScrollManager {
public:

	ScrollManager(Player*player1, Player*player2, MapManager*map);

	void Update();

	void Scroll();

	void MaxScroll();

private:

	Player * m_p_player_list[Player::MAX];
	MapManager * m_p_map;
};