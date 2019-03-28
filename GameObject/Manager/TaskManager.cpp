#include"TaskManager.h"
#include"../PrototypeEnemy/PrototypeEnemyManager.h"


// ここに管理を抽象クラスに入れる
TaskManager::TaskManager(std::vector<Object*>&obj) {
	
	m_mng_data.emplace_back(new EnemyManager(obj));
}



void TaskManager::Update() {
	
	// 生成と削除を回す
	for (auto&itr : m_mng_data) {
		itr->Entry();
		itr->Exit();
	}
}