#pragma once
#include"../Manager/ManagerBase.h"
#include"./PrototypeEnemy.h"
#include"../ObjectConnector.h"
#include"../Manager/ManagerBase.h"

/* マネージャークラスの例 */

// ここで敵を管理できるようにする
class EnemyManager : public ManagerBase {
public:

	// 親のコンストラクタを公開する
	using ManagerBase::ManagerBase;

	EnemyManager(ObjectManager*obj_and_mng);

	void Update()override;

private:

	// ここにオブジェクトを置いて管理する
	std::vector<Enemy*>m_enemy;
	// オブジェクト管理
	ObjectManager*m_obj_mng;
};
