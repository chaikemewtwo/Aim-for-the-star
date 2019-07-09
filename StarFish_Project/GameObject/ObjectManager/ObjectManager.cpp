#include"ObjectManager.h"
#include"../../Player/PlayerManager.h"
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
	// HACK:引数をm_p_player_mngで管理できるようにする
	m_p_player_mng = new PlayerManager(this);
	// 敵管理生成
	m_p_enemy_mng = new EnemyManager(this);
	// ロープ生成
	m_p_rope = new Rope(m_p_player_mng);
	// スタミナGameUI生成
	m_p_ui = new GameUI(m_p_player_mng);
	// マップ管理生成
	m_p_map_mng = new MapManager(m_p_player_mng, m_p_enemy_mng, this);
	// 当たり判定管理生成
	m_p_collision_mng = new CollisionManager(m_p_player_mng, m_p_enemy_mng);

	// オブジェクト登録
	Entry(m_p_rope);
	/*Entry(m_p_player[0]);
	Entry(m_p_player[1]);*/
	Entry(m_p_ui);
}

ObjectManager::~ObjectManager() {

	// オブジェクトリスト削除
	for (auto&obj : m_obj_list) {
		delete &obj;
	}

	// 描画用オブジェクトリスト要素削除
	m_draw_obj_list.clear();
}


void ObjectManager::Update() {
	// プレイヤー管理クラス更新
	m_p_player_mng->Update();
	// 敵管理クラス更新
	m_p_enemy_mng->Update();

	// 描画用オブジェクトをソートする
	SortDrawObject();

	// 更新
	for (auto&itr : m_obj_list) {

		itr.second->Update();
	}

	// 当たり判定
	m_p_collision_mng->Collision();
}


void ObjectManager::Draw() {

	// 描画用オブジェクト描画
	for (auto &itr : m_draw_obj_list) {
		(*itr).Draw();
	}
}


void ObjectManager::SortDrawObject(){

	// 一旦他のコンテナに入れ替えないといけない

	// 前のを削除
	std::vector<Object*>().swap(m_draw_obj_list);
	m_draw_obj_list.clear();
	
	
	// 要素を全て入れる。
	for (auto itr = m_obj_list.begin(); itr != m_obj_list.end();++itr) {

		m_draw_obj_list.push_back(itr->second);
	}

	// 昇順ソートを行う
	std::sort(m_draw_obj_list.begin(), m_draw_obj_list.end(),
		[](const Object*obj1, const Object*obj2) {
		return obj1->GetSortNum() < obj2->GetSortNum();
	});
}


void ObjectManager::Entry(Object*obj) {

	// nullなら戻す
	if (obj == nullptr) {
		return;
	}

	// 生成専用id
	unsigned int create_id = 0;

	//create_id = m_current_max_id;
	//m_current_max_id++;

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


void ObjectManager::ObjectListInit() {

	// 前のを削除
	std::vector<Object*>().swap(m_draw_obj_list);
	m_draw_obj_list.clear();
}


void ObjectManager::Exit(unsigned int id) {

	// 使い終わったidを保存
	m_used_id_list.push_back(id);

	// Objectの配列番号の要素を削除
	m_obj_list.erase(id);
}


// 活動していない場合メモリ削除
void ObjectManager::NotActiveIsDelete() {

	// 敵の配列
	auto obj = m_obj_list.begin();

	for (; obj != m_obj_list.end();) {

		// 活動を停止したら
		if (obj->second->IsActive() == false) {

			if (&obj == nullptr) {
				return;
			}

			// メモリの削除
			delete &obj;
			// 敵の要素の削除
			obj = m_obj_list.erase(obj);
		}
		else {
			obj++;
		}
	}
}


void ObjectManager::Delete(unsigned int id) {
	delete m_obj_list.at(id);
}


bool ObjectManager::IsClear()const{
	
	// マップの背景とチップが最大で、かつ自機の位置が200.fよりも少ない(上)のとき
	//if (m_p_map_mng->IsMaxMapRange() == true && m_p_player[0]->GetPos().y <= 200.f ||
	//	m_p_map_mng->IsMaxMapRange() == true && m_p_player[1]->GetPos().y <= 200.f) {
	//	return true;
	//}
	if (m_p_map_mng->IsMaxMapRange() == true && m_p_player_mng->GetPosRelay(Player::STAR_1).y <= 200.f ||
		m_p_map_mng->IsMaxMapRange() == true && m_p_player_mng->GetPosRelay(Player::STAR_2).y) {
		return true;
	}
		return false;
}


bool ObjectManager::IsGameOver()const {
	//if (m_p_player[0]->IsActive() == false && m_p_player[1]->IsActive() == false) {
	//	return true;
	//}
	if (m_p_player_mng->IsActiveRelay(Player::STAR_1) == false && m_p_player_mng->IsActiveRelay(Player::STAR_2) == false) {
		return true;
	}
	return false;
}
