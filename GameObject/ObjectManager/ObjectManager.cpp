#include"ObjectManager.h"
#include"../../CollisionObject/CollisionManager.h"



ObjectManager::ObjectManager() {

	// 当たり判定管理所を作る
	m_pcol_mng = new CollisionManager(m_p1,m_p2);
}


void ObjectManager::Update() {

	// 更新
	for (auto&itr : m_obj_lists) {

		itr->Update();
	}

	// 当たり判定
	m_pcol_mng->Collision();
}


void ObjectManager::Draw() {

	// 描画
	for (auto&itr : m_obj_lists) {
		itr->Draw();
	}
}


void ObjectManager::Entry(Object*obj) {

	// Objectの要素を追加
	m_obj_lists.emplace_back(obj);
}

void ObjectManager::Exit(int id) {

	// Objectの配列番号の要素を削除
	m_obj_lists.erase(m_obj_lists.begin() + id);
}