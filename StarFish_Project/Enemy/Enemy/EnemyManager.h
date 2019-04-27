#pragma once

#include<vector>
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"EnemyBase.h"

class EnemyBase;
// 敵の生成最大数(仮)
const int Enemy_Max_Num = 10;

class EnemyManager {
public:
	EnemyManager(ObjectManager* obj_mng);
	~EnemyManager();

	void Update();	// 更新
	void Draw();	// 描画
	void Create();	// 敵の生成
	void Delete();	// 敵の削除

private:
	// 生成した敵の配列
	std::vector<EnemyBase*> m_enemy_list;
	// オブジェクトのポインタ変数
	ObjectManager* m_pobj_mng;
};
