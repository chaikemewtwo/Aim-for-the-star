#pragma once
#include"../MapClass/Map/MapManager.h"
#include"../MapClass/PosConnecter.h"
#include"../MapClass/Player/Player.h"




class GameScene {
public:

	void Update() {
		m_map_mng.Update();
		m_pplayer.Update();
	}

	void Draw() {
		m_map_mng.Draw();
		m_pplayer.Draw();
	}

private:

	MapManager m_map_mng;
	Player m_pplayer;
};