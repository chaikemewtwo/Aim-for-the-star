#pragma once
#include"../Manager/ManagerBase.h"
#include"./PrototypeEnemy.h"



/* マネージャークラスの例 */

// ここで敵を管理できるようにする
class EnemyManager : public ManagerBase {
public:

	// 親のコンストラクタを公開する
	using ManagerBase::ManagerBase;

	Object* GetAfterTheEntry()override;
	std::vector<Object*> GetAfterTheBatchEntry()override;
	void Exit()override;

private:

	// ここにオブジェクトを置いて管理する
	std::vector<Enemy*>m_enemy;

	// 渡す用
	std::vector<Object*>m_batch_obj;
};
