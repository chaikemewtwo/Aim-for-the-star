#include"./PrototypeEnemyManager.h"




EnemyManager::EnemyManager(ObjectManager*obj_mng) {

	// オブジェクトを入れる
	if (m_obj_mng != nullptr) {
		m_obj_mng = obj_mng;
	}
}

void EnemyManager::Update() {

	// 生成
	m_enemy.emplace_back(new Enemy);
	m_obj_mng->Entry(m_enemy.back());
	m_id++;

	// 削除
	delete m_enemy.at(m_id);
	m_obj_mng->Exit(m_id);

}