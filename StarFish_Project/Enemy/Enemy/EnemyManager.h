#pragma once

#include<vector>
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../../Map/MapChip/MapChip.h"
#include"../../Blind/Blind.h"
#include"EnemyBase.h"


class EnemyManager {
public:
	EnemyManager(ObjectManager* obj_mng);
	~EnemyManager();
	
	void Update();	
	void Draw();
	void EnemyCreate(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2, int enemy_num);
	void BlindCreate(D3DXVECTOR2 pos, D3DXVECTOR2 goal);
	void Delete();

	// 生成されている敵の総数を返す関数
	int GetEnemyTotal();	
	// 敵の指定された敵の関数を返す関数
	EnemyBase* GetEnemyInstance(int num);

private:
	// 敵生成時の指定用定数
	enum EnemyType {
		SEAURCHIN = 1,
		NO_MOVE_SEAURCHIN,
		SELLFISH,
		ENEMYTYPE_MAX
	};

	std::vector<EnemyBase*> m_enemy_list;	// 生成した敵の配列

	ObjectManager* m_pobj_mng;				
	Blind* m_pblind;						
};
