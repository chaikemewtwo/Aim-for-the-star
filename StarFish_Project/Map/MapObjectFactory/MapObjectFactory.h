#pragma once
#include"../MapChip/MapChip.h"


// マップオブジェクトを生成するクラス

class MapObjectFactory {
public:

	MapObjectFactory(Map*map);

	void Create(int create_line, int create_chip_x, int create_chip_y, int chip_num);
	void Destory(int destory_line, int destory_chip_x, int destory_chip_y, bool *is_active);
	void EnemyCreate(int x, int y, int chip_num);
	void RockChipCreate(int x, int y, int chip_num);

private:
	Map * m_map;
};