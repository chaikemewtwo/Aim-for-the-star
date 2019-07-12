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
	Entry(m_p_ui);
}

ObjectManager::~ObjectManager() {

	// オブジェクトリスト削除
	for (auto&obj : m_p_object_list) {
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

	// 更新
	for (auto&itr : m_p_object_list) {

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
	for (auto itr = m_p_object_list.begin(); itr != m_p_object_list.end();++itr) {

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


	// Objectの要素を追加
	m_p_object_list[create_id] = obj;

	// Objectの最新のidをセット
	m_p_object_list.at(create_id)->SetId(create_id);
}


void ObjectManager::InitDrawObjectList() {

	// 前のを削除
	std::vector<Object*>().swap(m_draw_obj_list);
	m_draw_obj_list.clear();
}


void ObjectManager::Exit(unsigned int id) {

	// Objectの配列番号の要素を削除
	m_p_object_list.erase(id);
}


void ObjectManager::Exit(Object*object) {
	
	// Objectの配列番号の要素を削除
	m_p_object_list.erase(object->GetId());
}


//void ObjectManager::MemoryDelete(unsigned int id) {
//	delete m_p_object_list.at(id);
//}


bool ObjectManager::IsClear()const{
	
	// マップの背景とチップが最大で、かつ自機の位置が200.fよりも少ない(上)のとき
	if (m_p_map_mng->IsMaxMapRange() == true && m_p_player_mng->GetPosRelay(Player::STAR_1).y <= 200.f ||
		m_p_map_mng->IsMaxMapRange() == true && m_p_player_mng->GetPosRelay(Player::STAR_2).y <= 200.f) {
		return true;
	}
		return false;
}


bool ObjectManager::IsGameOver()const {
	if (m_p_player_mng->IsActiveRelay(Player::STAR_1) == false && m_p_player_mng->IsActiveRelay(Player::STAR_2) == false) {
		return true;
	}
	return false;
}
