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
	m_p_player[0] = new Player(Player::STAR_1);
	m_p_player[1] = new Player(Player::STAR_2);
	// 敵管理生成
	m_p_enemy_mng = new EnemyManager(this);
	// ロープ生成
	m_p_rope = new Rope(m_p_player[0], m_p_player[1]);
	// スタミナGameUI生成
	m_p_ui = new GameUI(m_p_player[0], m_p_player[1]);
	// マップ管理生成
	m_p_map_mng = new MapManager(m_p_player[0], m_p_player[1], m_p_enemy_mng, this);
	// 当たり判定管理生成
	m_p_collision_mng = new CollisionManager(m_p_player[0], m_p_player[1], m_p_enemy_mng);

	// オブジェクト登録
	Entry(m_p_rope);
	Entry(m_p_player[0]);
	Entry(m_p_player[1]);
	Entry(m_p_ui);
}

ObjectManager::~ObjectManager() {

	// オブジェクトリスト削除
	for (auto&obj : m_object_list) {
		delete &obj;
	}

	// 描画用オブジェクトリスト要素削除
	m_draw_obj_list.clear();
}


void ObjectManager::Update() {

	// 敵管理クラス更新
	m_p_enemy_mng->Update();

	// 更新
	for (auto&itr : m_object_list) {

		itr.second->Update();
	}

	// 当たり判定
	m_p_collision_mng->Collision();

	// 描画用オブジェクトをソートする
	EntryAndSortDrawObject();
}


void ObjectManager::Draw() {

	// 描画用オブジェクト描画
	for (auto &itr : m_draw_obj_list) {
		(*itr).Draw();
	}
}


void ObjectManager::EntryAndSortDrawObject(){

	// 前のリストを削除
	InitDrawObjectList();
	
	// 要素を全て入れる。
	for (auto itr = m_object_list.begin(); itr != m_object_list.end();++itr) {

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

	create_id = m_current_the_newest_id;
	m_current_the_newest_id++;

	//// idの空きがないなら
	//if (m_reuse_id_list.empty() != 0) {
	//
	//	// 生成idに現在最大のidを入れる
	//	create_id = m_current_newest_id;
	//	// 最新idにする
	//	m_current_newest_id++;
	//}
	//// 使われていないid番号があるなら
	//else {
	//
	//	for (unsigned int i = 0; i < m_reuse_id_list.size(); i++) {
	//
	//		// idがすでに使われているか
	//		auto itr = m_object_list.find(m_reuse_id_list[i]);
	//
	//		// 設定されているなら
	//		if (itr != m_object_list.end()) {
	//			continue;
	//		}
	//
	//		/* ここまできたら設定されていない */
	//
	//		// 最初に入っているidを入れる
	//		create_id = m_reuse_id_list[i];
	//		// idを渡したので使っているとみなして要素を消す
	//		m_reuse_id_list.erase(m_reuse_id_list.begin() + i);
	//
	//		break;
	//	}
	//}

	// Objectの要素を追加
	m_object_list[create_id] = obj;

	// Objectの最新のidをセット
	m_object_list.at(create_id)->SetId(create_id);
}




void ObjectManager::InitDrawObjectList() {

	// 前のを削除
	std::vector<Object*>().swap(m_draw_obj_list);
	m_draw_obj_list.clear();
}


void ObjectManager::Exit(unsigned int id) {

	// 使い終わったidを保存
	m_reuse_id_list.push_back(id);

	// Objectの配列番号の要素を削除
	m_object_list.erase(id);
}


void ObjectManager::Exit(Object*object) {
	// 使い終わったidを保存
	m_reuse_id_list.push_back(object->GetId());

	// Objectの配列番号の要素を削除
	m_object_list.erase(object->GetId());
}


void ObjectManager::MemoryDelete(unsigned int id) {
	delete m_object_list.at(id);
}


bool ObjectManager::IsClear()const{
	
	// マップの背景とチップが最大で、かつ自機の位置が200.fよりも少ない(上)のとき
	if (m_p_map_mng->IsMaxMapRange() == true && m_p_player[0]->GetPos().y <= 200.f ||
		m_p_map_mng->IsMaxMapRange() == true && m_p_player[1]->GetPos().y <= 200.f) {
		return true;
	}
		return false;
}


bool ObjectManager::IsGameOver()const {
	if (m_p_player[0]->IsActive() == false && m_p_player[1]->IsActive() == false) {
		return true;
	}
	return false;
}
