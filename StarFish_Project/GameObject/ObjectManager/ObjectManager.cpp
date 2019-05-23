#include"ObjectManager.h"
#include"../../Enemy/Enemy/EnemyManager.h"
#include"../../Player/Player.h"
#include"../../Map/MapChip/MapChip.h"
#include"../../GameUI/GameUI.h"
#include"../../Map/MapManager/MapManager.h"
#include"../../Rope/Rope.h"
#include"../Object/Object.h"
#include"../../CollisionObject/CollisionManager.h"

#include<algorithm>
#include<iostream>



ObjectManager::ObjectManager(){

	// プレイヤー生成
	m_pplayer[0] = new Player(Player::STAR_1);
	m_pplayer[1] = new Player(Player::STAR_2);
	// 敵管理生成
	m_pe_mng = new EnemyManager(this);
	// ロープ生成
	m_prope = new Rope(m_pplayer[0], m_pplayer[1]);
	// スタミナGameUI生成
	m_pui = new GameUI(m_pplayer[0], m_pplayer[1]);
	// マップ管理生成
	m_pm_mng = new MapManager(m_pplayer[0], m_pplayer[1], m_pe_mng, this);
	// 当たり判定管理生成
	m_pcol_mng = new CollisionManager(m_pplayer[0], m_pplayer[1], m_pe_mng);



	// オブジェクト登録
	Entry(m_prope);
	Entry(m_pplayer[0]);
	Entry(m_pplayer[1]);
	Entry(m_pui);
	
}


void ObjectManager::Update() {

	// 敵管理クラス更新
	m_pe_mng->Update();

	// 描画用オブジェクトをソートする
	DrawObjSort();

	// 更新
	for (auto&itr : m_obj_list) {

		itr.second->Update();
	}

	// 当たり判定
	m_pcol_mng->Collision();

}


void ObjectManager::Draw() {

	// 描画用オブジェクト描画
	for (auto &itr : m_draw_obj_list) {
		(*itr).Draw();
	}
}


void ObjectManager::DrawObjSort(){

	// 一旦他のコンテナに入れ替えないといけない
	// 描画用の配列を作る
	
	// 前のを削除
	m_draw_obj_list.clear();
	std::vector<Object*>().swap(m_draw_obj_list);
	
	// 要素を全て入れる。
	for (auto itr = m_obj_list.begin(); itr != m_obj_list.end();++itr) {

		m_draw_obj_list.push_back(itr->second);
	}

	// 昇順ソートを行う
	std::sort(m_draw_obj_list.begin(), m_draw_obj_list.end(),
		[](const Object*x, const Object*y) {
		return x->GetSortNum() < y->GetSortNum();
	});
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

