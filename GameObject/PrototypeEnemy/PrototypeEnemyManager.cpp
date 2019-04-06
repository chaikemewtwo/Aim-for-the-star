#include"./PrototypeEnemyManager.h"
#include"../ObjectManager.h"



// 親のコンストラクタも行う
EnemyManager::EnemyManager(ObjectManager*obj_mng) : ManagerBase(obj_mng) {

	// オブジェクトを入れる
	if (obj_mng != nullptr) {
		m_obj_mng = obj_mng;
	}
	m_current_id = 0;
}

void EnemyManager::Update() {

	// 生成
	m_enemy_lists.emplace_back(new Enemy);
	// 一番後ろが最新なので後ろから入れる
	m_obj_mng->Entry(m_enemy_lists.back().get());
	// idを加算する
	m_current_id++;

	
	// 配列の削除
	m_obj_mng->Exit(m_current_id);
	// idを減算する
	m_current_id--;

}