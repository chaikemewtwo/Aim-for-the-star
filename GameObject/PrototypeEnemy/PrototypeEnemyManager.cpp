#include"./PrototypeEnemyManager.h"
#include"../ObjectManagerToDoRegistr.h"



// 親のコンストラクタも行う
EnemyManager::EnemyManager(ObjectManagerToDoRegistr*obj_mng) : ManagerBase(obj_mng) {

	// オブジェクトを入れる
	if (obj_mng != nullptr) {
		m_obj_mng = obj_mng;
	}
	m_id = 0;
}

void EnemyManager::Update() {

	// 生成
	m_enemy.emplace_back(new Enemy);
	// 一番後ろが最新なので後ろから入れる
	m_obj_mng->Entry(m_enemy.back().get());
	// idを加算する
	m_id++;

	
	// 配列の削除
	m_obj_mng->Exit(m_id);
	// idを減算する
	m_id--;

}