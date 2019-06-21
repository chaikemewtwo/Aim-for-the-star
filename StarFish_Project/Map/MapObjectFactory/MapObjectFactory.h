#pragma once
#include"../MapChip/MapChip.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include"../BedRockChip/BedRockChip.h"

// マップオブジェクトを生成するクラス


class MapObjectFactory {
public:

	MapObjectFactory(Map*map,EnemyManager*enemy_mng,Player * player1,Player * player2,ObjectManager*obj_mng);

	void Init();
	void Update();

	void Create(int create_line_y);
	void Destory(int destory_line_y);

private:

	// 上の生成線
	static constexpr int CREATE_LINE_UP = 16;
	// 下の生成線
	static constexpr int CREATE_LINE_DOWN = 3;
	// 上の生成線
	static constexpr int DESTORY_LINE_UP = CREATE_LINE_UP + 1;
	// 下の生成線
	static constexpr int DESTORY_LINE_DOWN = CREATE_LINE_DOWN - 1;
	
private:

	void EnemyCreate(int x, int y);
	void RockChipCreate(int x, int y);

private:
	Map * m_p_map;
	EnemyManager * m_p_enemy_mng;
	Player *m_p_player[2];
	ObjectManager * m_p_obj_mng;

	// BedRockChipの配列を持つ
	std::vector<BedRockChip*>m_rock_chip_list;
};
