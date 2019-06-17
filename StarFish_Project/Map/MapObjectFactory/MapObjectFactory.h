#pragma once
#include"../MapChip/MapChip.h"
#include"../../Enemy/Enemy/EnemyManager.h"

// マップオブジェクトを生成するクラス

class MapObjectFactory {
public:

	MapObjectFactory(Map*map,EnemyManager*enemy_mng,Player * player1,Player * player2,ObjectManager*obj_mng);

	void Create(int create_line, int create_chip_x, int create_chip_y, int chip_num, bool *is_active);
	void Destory(int destory_line, int destory_chip_x, int destory_chip_y, bool *is_active);
	
private:

	void EnemyCreate(int x, int y, int chip_num);
	void RockChipCreate(int x, int y, int chip_num);

private:
	Map * m_p_map;
	EnemyManager * m_p_enemy_mng;
	Player *m_p_player[2];
	ObjectManager * m_p_obj_mng;
};
