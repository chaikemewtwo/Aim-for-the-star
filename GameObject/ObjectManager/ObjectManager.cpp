#include"ObjectManager.h"
#include"../../CollisionObject/CollisionManager.h"
#include"../../PrototypeEnemy/PrototypeEnemyManager.h"


ObjectManager::ObjectManager() {

	// 当たり判定管理所を作る
	//m_pcol_mng = new CollisionManager(m_p1,m_p2);

	m_pe_mng = new EnemyManager(this);
}


void ObjectManager::Update() {

	// 敵管理クラス更新
	m_pe_mng->Update();

	// 更新
	for (auto&itr : m_obj_lists) {

		itr->Update();
	}

	// 当たり判定
	//m_pcol_mng->Collision();
}


void ObjectManager::Draw() {

	// 描画
	for (auto&itr : m_obj_lists) {
		itr->Draw();
	}
}


void ObjectManager::Entry(Object*obj) {

	if (nullptr != obj) {
		
		// Objectの要素を追加
		m_obj_lists.emplace_back(obj);

		// idリストにObjectのid登録
		m_id_lists.push_back(m_current_id);
		// Objectの最新のidをセット
		m_obj_lists.at(m_id_lists[m_current_id])->SetId(m_id_lists[m_current_id]);
		
		// 最新のid更新
		m_current_id++;
	}
}

void ObjectManager::Exit(int id) {

	
	// 消す前にnullptrを代入させる
	//m_obj_lists[id] = nullptr;

	// Objectの配列番号の要素を削除
	m_obj_lists.erase(m_obj_lists.begin() + id);

	// idリストの特定の位置を削除
	m_id_lists.erase(m_id_lists.begin() + id);

	// 最新位置を減算(最大値)
	m_current_id--;
}


/*
void ObjectManager::IsNotActiveExit() {

	for (auto obj_itr = m_obj_lists.begin(); obj_itr != m_obj_lists.end();) {

		// 死亡フラグオンなら削除
		if (obj_itr->get()->GetIsActive() == true) {

			// 配列の削除
			obj_itr = m_obj_lists.erase(obj_itr);

			// idリストの特定の位置を削除
			m_id_lists.erase(m_id_lists.begin() + obj_itr->get()->GetId());

			// 最新位置を減算
			m_current_id--;
		}
		// そうでなければ加算
		else {
			obj_itr++;
		}
	}

}
*/