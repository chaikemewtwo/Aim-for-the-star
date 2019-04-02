#pragma once
#include"../Manager/ManagerBase.h"
#include"./PrototypeEnemy.h"
#include"../ObjectConnector.h"

/* マネージャークラスの例 */

// ここで敵を管理できるようにする
class EnemyManager : public ManagerBase {
public:

	EnemyManager();

	void ObjectConnectorEntry(ObjectConnector*cca_mng)override;

	void Exit()override;

private:

	// ここにオブジェクトを置いて管理する
	std::vector<Enemy*>m_enemy;
	Enemy*enemy1;
	Enemy*enemy2;
};
