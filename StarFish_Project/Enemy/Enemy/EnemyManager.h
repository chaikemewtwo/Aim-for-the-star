#pragma once

#include<vector>
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"EnemyBase.h"

class EnemyBase;


class EnemyManager {
public:
	EnemyManager(ObjectManager* obj_mng);
	~EnemyManager();
	
	void Update();	
	void Draw();
	void Create(float x, float y);
	void Delete();

	// 生成されている敵の総数を返す関数
	int GetEnemyTotal();	

private:
	// 敵の生成最大数(仮)
	const int Enemy_Max_Num = 10;
	// 生成した敵の配列
	std::vector<EnemyBase*> m_enemy_list;
	// オブジェクトのポインタ変数
	ObjectManager* m_pobj_mng;
};
