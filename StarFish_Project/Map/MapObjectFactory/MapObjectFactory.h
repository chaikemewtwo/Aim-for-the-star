#pragma once
#include"../MapChip/MapChip.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include"../BedRockChip/RockChip.h"

// マップオブジェクトを生成するクラス


class MapObjectFactory {
public:

	MapObjectFactory(Map*map,EnemyManager*enemy_mng, PlayerManager*player_mng,ObjectManager*obj_mng);

	void Init();
	void Update();

	void CreateWidthLine(int create_line_y);
	void DestoryWidthLine(int destory_line_y);

private:
	
private:

	void EnemyCreate(int x, int y);
	void RockChipCreate(int x, int y);

private:
	Map * m_p_map;
	PlayerManager * m_p_player_mng;
	EnemyManager  * m_p_enemy_mng;
	ObjectManager * m_p_obj_mng;

	// BedRockChipの配列を持つ
	std::vector<RockChip*>m_rock_chip_list;
};
