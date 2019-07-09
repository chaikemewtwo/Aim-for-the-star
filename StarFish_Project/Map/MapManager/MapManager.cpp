#include"MapManager.h"
#include"../../Player/Player.h"
#include"../MapChip/MapChip.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../MapChip/MapChip.h"
#include"../BackGround/BackGround.h"



MapManager::MapManager(PlayerManager*p_mng, EnemyManager*e_mng, ObjectManager*obj_mng) {

	// nullチェック
	if (p_mng == nullptr) {
		return;
	}
	if (e_mng == nullptr) {
		return;
	}
	if (obj_mng == nullptr) {
		return;
	}

	// マップ生成
	m_p_map = new Map(p_mng, e_mng, obj_mng);

	// 背景生成
	m_p_bg1 = new BackGround(
		// 読み込むテキスト名
		"Map/BGData/BG1.csv",
		// マップ実体
		m_p_map,
		// ソートオブジェクトの型
		BEFORE_BG,
		// 指定したサイズを基準にスクロール
		(Texture::Size::GetGraphSizeX("Resource/Texture/Map/bg_hero_01.png")),
		(Texture::Size::GetGraphSizeY("Resource/Texture/Map/bg_hero_01.png")));


	// マップ登録
	obj_mng->Entry(m_p_map);
	// 背景1登録
	obj_mng->Entry(m_p_bg1);


	//// 背景2
	//obj_mng->Entry(
	//	m_p_bg2 = new BackGround(
	//		// 読み込むテキスト名
	//		"Map/BGData/BG2.csv",
	//		// マップ実体
	//		m_p_map,
	//		// ソートオブジェクトの型
	//		AFTER_BG,
	//		// 指定したサイズを基準にスクロール
	//	(Texture::Size::GetGraphSizeX("Resource/Texture/Map/bg_hero_01.png")),
	//	(Texture::Size::GetGraphSizeY("Resource/Texture/Map/bg_hero_01.png")))
	//);
}


MapManager::~MapManager() {

	// マップデータが入っている場合は削除する
	if (m_p_map != nullptr) {

		// マップの削除
		m_p_map = nullptr;
		delete m_p_map;
	}
}


void MapManager::Update() {

	// nullチェック
	if (m_p_map == nullptr) {
		return;
	}
	if (m_p_bg1 == nullptr) {
		return;
	}

	// マップ関連更新
	m_p_map->Update();
	m_p_bg1->Update();

}


void MapManager::Draw(){

	// 描画
	m_p_bg1->Draw();
	m_p_map->Draw();
}


Map MapManager::GetMapInstance()const {
	return *m_p_map;
}


float MapManager::GetMaxMapPos()const {
	return m_p_bg1->GetMaxMapPos();
}


bool MapManager::IsMaxMapRange()const {
	return m_p_map->IsMaxScroll();
}
