#include"ObjectManagerToDoRegistr.h"
#include"../GameObject/PrototypeEnemy/PrototypeEnemyManager.h"



ObjectManagerToDoRegistr::ObjectManagerToDoRegistr() {

	// 管理クラス生成
	m_mng_lists.emplace_back(new EnemyManager(this));
}


void ObjectManagerToDoRegistr::Update() {

	// 更新
	for (auto&itr : m_obj_lists) {

		itr->Update();
	}

	// 生成と削除を回す
	for (auto&itr : m_mng_lists) {

		itr->Update();
	}
}


void ObjectManagerToDoRegistr::Draw() {

	// 描画
	for (auto&itr : m_obj_lists) {
		itr->Draw();
	}
}


void ObjectManagerToDoRegistr::Entry(Object*obj) {

	// Objectの要素を追加
	m_obj_lists.emplace_back(obj);
}

void ObjectManagerToDoRegistr::Exit(int id) {

	// Objectの配列番号の要素を削除
	m_obj_lists.erase(m_obj_lists.begin() + id);
}