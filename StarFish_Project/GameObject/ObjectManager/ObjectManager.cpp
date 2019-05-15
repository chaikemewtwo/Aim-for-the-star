#include"ObjectManager.h"
#include"../../CollisionObject/CollisionManager.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include"../../Player/Player.h"
#include"../../Map/MapChip/MapChip.h"
#include<algorithm>
#include"../../StaminaUI/StaminaUI.h"
#include"../../Map/MapManager/MapManager.h"



ObjectManager::ObjectManager(){

	// 敵管理生成
	m_pe_mng = new EnemyManager(this);

	// 自機生成＆objectに登録
	Entry(m_pplayer[0] = new Player(Player::STAR_1));
	Entry(m_pplayer[1] = new Player(Player::STAR_2));
	// スタミナUI生成
	Entry(m_pstamina_ui = new StaminaUI(m_pplayer[0], m_pplayer[1]));
	// マップ管理生成
	m_pm_mng = new MapManager(m_pplayer[0],m_pplayer[1],m_pe_mng);
	// 当たり判定管理を作る
	m_pcol_mng = new CollisionManager(m_pplayer[0],m_pplayer[1],m_pe_mng);
}


void ObjectManager::Update() {

	// 敵管理クラス更新
	m_pe_mng->Update();

	// マップ管理クラス更新
	m_pm_mng->Update();

	// 更新
	for (auto&itr : m_obj_lists) {

		itr.second->Update();
	}

	// 当たり判定
	m_pcol_mng->Collision();

}


void ObjectManager::Draw() {

	// マップ管理クラス描画
	m_pm_mng->Draw();

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

