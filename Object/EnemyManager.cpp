#include"EnemyManager.h"


EnemyManager::EnemyManager(std::vector<Object*>&object) {
	m_object = &object;
	m_id = 0;
}


template<class T>
// オブジェクト代入
void EnemyManager::EnemyEntry(Object*obj, std::vector<T*>&vec) {

	vec.emplace_back(obj);

	// アップキャスト,最小値の要素を代入
	m_object->emplace_back(vec.back());
}

void EnemyManager::EnemyExit(std::vector<Object*>&vec, int index) {

	delete vec[index];
};