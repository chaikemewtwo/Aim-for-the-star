#pragma once
#include"../Manager/ManagerData.h"
#include"./PrototypeEnemy.h"



/* マネージャークラスの例 */

// ここで敵を管理できるようにする
class EnemyManager : public ManagerData {
public:

	// 親のコンストラクタを公開する
	using ManagerData::ManagerData;
	
	// 特定の位置を削除
	void EnemyExit(std::vector<Object*>&vec, int index);

	// HACK
	// 自分のvectorオブジェクトと抽象的なオブジェクトに新しいオブジェクト代入
	//void VectorObjectEntry(Object*obj, std::vector<Enemy*>&vec);

	void Entry()override;
	void Exit()override;

private:

	// ここにオブジェクトを置いて管理する
	std::vector<Enemy*>m_enemy;
};
