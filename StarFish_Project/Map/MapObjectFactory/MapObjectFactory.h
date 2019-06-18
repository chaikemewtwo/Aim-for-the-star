#pragma once
#include"../MapChip/MapChip.h"
#include"../../Enemy/Enemy/EnemyManager.h"


// マップオブジェクトを生成するクラス


class MapObjectFactory {
public:

	MapObjectFactory(Map*map,EnemyManager*enemy_mng,Player * player1,Player * player2,ObjectManager*obj_mng);

	void Update();

	void Create(int create_line_y);
	void Destory(int destory_line_y);
	
private:

	void EnemyCreate(int x, int y);
	void RockChipCreate(int x, int y);

private:
	Map * m_p_map;
	EnemyManager * m_p_enemy_mng;
	Player *m_p_player[2];
	ObjectManager * m_p_obj_mng;
};
