#include"ObjectManager.h"
#include"../../CollisionObject/CollisionManager.h"
#include"../../PrototypeEnemy/PrototypeEnemyManager.h"
#include<algorithm>



ObjectManager::ObjectManager() {

	// TODO 当たり判定管理を作る
	//m_pcol_mng = new CollisionManager(m_pp[0],m_pp[1]);

	m_pe_mng = new EnemyManager(this);
}


void ObjectManager::Update() {

	// 敵管理クラス更新
	m_pe_mng->Update();

	// 更新
	for (auto&itr : m_obj_lists) {

		itr.second->Update();
	}

	// TODO 当たり判定
	//m_pcol_mng->Collision();
}


void ObjectManager::Draw() {

	// 描画
	for (auto &itr : m_obj_lists) {

		itr.second->Draw();
	}
}


void ObjectManager::Entry(Object*obj) {

	// nullなら戻す
	if (nullptr == obj) {
		return;
	}

	// 生成専用id
	unsigned int create_id = 0;

	// idの空きがないなら最新idを作る
	if (m_used_id_lists.empty() != 0) {

		// 生成idに現在最大のidを入れる
		create_id = m_current_max_id;
		// 最新idにする
		m_current_max_id++;
	}
	// 使われていないid番号があるなら
	else {

		for (unsigned int i = 0; i < m_used_id_lists.size(); i++) {

			// idがすでに使われているか
			auto itr = m_obj_lists.find(m_used_id_lists[i]);

			// 設定されているなら
			if (itr != m_obj_lists.end()) {
				continue;
			}

			/* ここまできたら設定されていない */

			// 最初に入っているidを入れる
			create_id = m_used_id_lists[i];
			// idを渡したので使っているとみなして要素を消す
			m_used_id_lists.erase(m_used_id_lists.begin() + i);

			break;
		}
	}

	// Objectの要素を追加
	m_obj_lists[create_id] = obj;

	// Objectの最新のidをセット
	m_obj_lists.at(create_id)->SetId(create_id);

}

void ObjectManager::Exit(unsigned int id) {

	// 使い終わったidを保存
	m_used_id_lists.push_back(id);

	// Objectの配列番号の要素を削除
	m_obj_lists.erase(id);
}

