#include"ObjectManager.h"
#include"../../CollisionObject/CollisionManager.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include"../../Player/Player.h"
#include"../../Map/MapChip/MapChip.h"
#include<algorithm>
#include"../../StaminaUI/StaminaUI.h"
#include"../../Map/MapManager/MapManager.h"
#include"../../Rope/Rope.h"



ObjectManager::ObjectManager(){

	// 敵管理生成
	m_pe_mng = new EnemyManager(this);

	// プレイヤー生成
	m_pplayer[0] = new Player(Player::STAR_1);
	m_pplayer[1] = new Player(Player::STAR_2);

	// ロープ生成
	Entry(m_prope = new Rope(m_pplayer[0], m_pplayer[1]));

	// 自機生成＆objectに登録
	Entry(m_pplayer[0]);
	Entry(m_pplayer[1]);
	
	// スタミナUI生成
	Entry(m_pstamina_ui = new StaminaUI(m_pplayer[0], m_pplayer[1]));
	// マップ管理生成
	m_pm_mng = new MapManager(m_pplayer[0], m_pplayer[1], m_pe_mng);
	// 当たり判定管理を作る
	m_pcol_mng = new CollisionManager(m_pplayer[0], m_pplayer[1], m_pe_mng);
}


void ObjectManager::Update() {

	// 敵管理クラス更新
	m_pe_mng->Update();

	// マップ管理クラス更新
	m_pm_mng->Update();

	// 描画用オブジェクトをソートする
	//Sort();

	// 更新
	for (auto&itr : m_obj_list) {

		itr.second->Update();
	}

	// 後の描画
	m_pm_mng->AfterUpdate();

	// 当たり判定
	m_pcol_mng->Collision();
}


void ObjectManager::Draw() {

	// マップ管理クラス描画
	m_pm_mng->Draw();

	// 描画
	for (auto &itr : m_obj_list){

		(itr).second->Draw();
	}

	m_pm_mng->AfterDraw();
}


void ObjectManager::Sort(){

	// 一旦他のコンテナに入れ替えないといけない
	// 描画用の配列を作る

	std::vector<Object*>::iterator swap;

	// 削除
	std::vector<Object*>(m_draw_obj_list).swap(m_draw_obj_list);
	m_draw_obj_list.clear();

	//for (int i = 0; i < m_draw_obj_list.size(); ++i) {
	//	if (m_draw_obj_list[i] != nullptr) {
	//		delete m_draw_obj_list[i];
	//	}
	//}

	// 要素を全て入れる。
	for (auto itr = m_obj_list.begin(); itr != m_obj_list.end();++itr) {
		m_draw_obj_list.emplace_back((itr)->second);
	}
	// ソートを行う
	for (auto itr = m_draw_obj_list.begin(); itr != m_draw_obj_list.end(); ++itr) {
		
		// 後の値より大きい場合(昇順)
		if ((*itr)->GetSortNum() > (*itr++)->GetSortNum()) {

			// 入れ替え
			swap = itr;
			itr = itr++;
			itr++ = swap;
		}
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
	if (m_used_id_list.empty() != 0) {

		// 生成idに現在最大のidを入れる
		create_id = m_current_max_id;
		// 最新idにする
		m_current_max_id++;
	}
	// 使われていないid番号があるなら
	else {

		for (unsigned int i = 0; i < m_used_id_list.size(); i++) {

			// idがすでに使われているか
			auto itr = m_obj_list.find(m_used_id_list[i]);

			// 設定されているなら
			if (itr != m_obj_list.end()) {
				continue;
			}

			/* ここまできたら設定されていない */

			// 最初に入っているidを入れる
			create_id = m_used_id_list[i];
			// idを渡したので使っているとみなして要素を消す
			m_used_id_list.erase(m_used_id_list.begin() + i);

			break;
		}
	}

	// Objectの要素を追加
	m_obj_list[create_id] = obj;

	// Objectの最新のidをセット
	m_obj_list.at(create_id)->SetId(create_id);

}

void ObjectManager::Exit(unsigned int id) {

	// 使い終わったidを保存
	m_used_id_list.push_back(id);

	// Objectの配列番号の要素を削除
	m_obj_list.erase(id);
}

