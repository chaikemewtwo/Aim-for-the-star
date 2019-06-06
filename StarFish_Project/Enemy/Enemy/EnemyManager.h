#pragma once

#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../../Blind/Blind.h"
#include"EnemyBase.h"


// 敵生成時の指定用定数
enum EnemyType {
	SEAURCHIN = 1,
	NO_MOVE_SEAURCHIN,
	SELLFISH,
	ENEMYTYPE_MAX
};


class EnemyManager {
public:
	EnemyManager(ObjectManager* obj_mng);
	~EnemyManager();
	
	void Update();	
	void Draw();
	// 敵生成関数
	void CreateEnemy(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2, EnemyType enemy_num);
	// ブラインド生成関数
	void CreateBlind(D3DXVECTOR2 pos, D3DXVECTOR2 goal);
	// 生成されている敵の総数を返す関数
	int GetEnemyTotal();	
	// 敵の指定された敵の関数を返す関数
	EnemyBase* GetEnemyInstance(int num);

private:
	void DeleteCheck();

private:
	std::vector<EnemyBase*> m_enemy_list;	// 生成した敵の配列

	ObjectManager* m_pobj_mng;				
	Blind* m_pblind;						
};
