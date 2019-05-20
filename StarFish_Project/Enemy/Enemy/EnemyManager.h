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
	void EnemyCreate(D3DXVECTOR2 pos, MapChip* map_chip, Player* p1, Player* p2);
	void BlindCreate(D3DXVECTOR2 pos, D3DXVECTOR2 goal);
	void Delete();

	// 生成されている敵の総数を返す関数
	int GetEnemyTotal();	
	// 敵の指定された敵の関数を返す関数
	EnemyBase* GetEnemyInstance(int num);

private:
	ObjectManager* m_pobj_mng;				// オブジェクトの格納変数
	Blind* m_pblind;						// ブラインドクラス格納変数
	std::vector<EnemyBase*> m_enemy_list;	// 生成した敵の配列

	const int Enemy_Max_Num = 10;			// 敵の生成最大数(仮)
};
