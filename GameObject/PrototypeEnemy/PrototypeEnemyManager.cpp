#include"./PrototypeEnemyManager.h"



Object* EnemyManager::GetAfterTheEntry() {

	// 生成
	
	//if()条件
	return new Enemy;

	// 無かったらNULLを返す
	return NULL;
}

void EnemyManager::Exit() {

}


std::vector<Object*> EnemyManager::GetAfterTheBatchEntry() {

m_enemy.emplace_back(new Enemy);
m_batch_obj.emplace_back(m_enemy.back());
m_enemy.emplace_back(new Enemy);
m_batch_obj.emplace_back(m_enemy.back());

return m_batch_obj;
}
