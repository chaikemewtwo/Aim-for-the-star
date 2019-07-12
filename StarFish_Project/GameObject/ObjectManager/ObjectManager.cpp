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
#include"../../ScrollManager/ScrollManager.h"



ObjectManager::ObjectManager(){


	// 敵管理生成
	m_p_enemy_mng = new EnemyManager(this);

	// プレイヤー1生成
	m_p_player[Player::STAR_1] = new Player(Player::STAR_1);

	// プレイヤー2生成
	m_p_player[Player::STAR_2] = new Player(Player::STAR_2);

	// プレイヤーオブジェクト登録
	Entry(m_p_player[Player::STAR_1]);
	Entry(m_p_player[Player::STAR_2]);

	// ロープ生成
	m_p_rope = new Rope(m_p_player[Player::STAR_1], m_p_player[Player::STAR_2]);

	// スタミナGameUI生成
	m_p_ui = new GameUI(m_p_player[Player::STAR_1], m_p_player[Player::STAR_2]);

	// マップ管理生成
	m_p_map_mng = new MapManager(m_p_enemy_mng, this);

	// 当たり判定管理生成
	m_p_collision_mng = new CollisionManager(m_p_player[Player::STAR_1], m_p_player[Player::STAR_2], m_p_enemy_mng,m_p_map_mng);

	// スクロール管理者生成
	m_p_scroll_manager = new ScrollManager(m_p_player[Player::STAR_1], m_p_player[Player::STAR_2], m_p_map_mng);

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
	m_draw_object_list.clear();
}


void ObjectManager::Update() {

	// 敵管理クラス更新
	m_p_enemy_mng->Update();

	// スクロールの管理者
	m_p_scroll_manager->Update();
	
	for (auto&itr : m_p_object_list) {

		// 更新
		itr.second->Update();
	}

	// 当たり判定
	m_p_collision_mng->Collision();

	// 描画用オブジェクトをソートする
	EntryAndSortDrawObject();
}


void ObjectManager::Draw() {

	// 描画用オブジェクト描画
	for (auto &obj : m_draw_object_list) {
		(*obj).Draw();
	}
}


void ObjectManager::EntryAndSortDrawObject(){

	// 前のリストを削除
	InitDrawObjectList();
	
	// 要素を全て入れる
	for (auto draw_object = m_p_object_list.begin(); draw_object != m_p_object_list.end();++draw_object) {

		m_draw_object_list.push_back(draw_object->second);
	}

	// 昇順ソートを行う
	std::sort(m_draw_object_list.begin(), m_draw_object_list.end(),
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
	std::vector<Object*>().swap(m_draw_object_list);
	m_draw_object_list.clear();
}


void ObjectManager::Exit(unsigned int id) {

	// 使い終わったidを保存
	m_reuse_id_list.push_back(id);

	// Objectの配列番号の要素を削除
	m_p_object_list.erase(id);
}


void ObjectManager::Exit(Object*object) {
	// 使い終わったidを保存
	m_reuse_id_list.push_back(object->GetId());

	// Objectの配列番号の要素を削除
	m_p_object_list.erase(object->GetId());
}


void ObjectManager::MemoryDelete(unsigned int id) {
	delete m_p_object_list.at(id);
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
