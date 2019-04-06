#pragma once
#include"./PrototypeEnemy.h"
#include"../Manager/ManagerBase.h"
#include<memory>



/* マネージャークラスの例.試作です */

// ここで敵を管理できるようにする
class EnemyManager : public ManagerBase {
public:

	// 親のコンストラクタも初期化する
	EnemyManager(ObjectManager*manager);

	void Update()override;

private:

	// ここにオブジェクトを置いて管理する
	std::vector<std::unique_ptr<Enemy>>m_enemy_lists;
	// オブジェクト管理
	ObjectManager*m_obj_mng;
};
