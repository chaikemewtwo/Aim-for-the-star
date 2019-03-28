#include"./PrototypeEnemyManager.h"



void EnemyManager::Entry() {

	// 生成
	ObjectEntry(new Enemy);
}

void EnemyManager::Exit() {

}


void EnemyManager::EnemyExit(std::vector<Object*>&vec, int index) {

	// vector型オブジェクトの値を削除
	delete vec[index];
};

// HACK
//void EnemyManager::VectorObjectEntry(Object*obj, std::vector<Enemy*>&vec) {
//
//	vec.emplace_back(obj);
//
//	// アップキャスト,最小値の要素を代入
//	m_object->emplace_back(vec.back());
//}