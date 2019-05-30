#include"MapManager.h"
#include"../../Player/Player.h"
#include"../MapChip/MapChip.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../MapChip/MapChip.h"
#include"../BackGround/BackGround.h"



MapManager::MapManager(Player*star1, Player*star2, EnemyManager*e_mng, ObjectManager*obj_mng) {

	// オブジェクト管理
	m_pobj_mng = obj_mng;

	// マップチップ
	obj_mng->Entry(m_pmap_tip = new Map(star1, star2, e_mng));

	// 背景1オブジェクト登録(こちらをメインにする)
	obj_mng->Entry(m_pbg = new
		BackGround("Map/BGData/BG1.csv",
			m_pmap_tip,
			BG_BEFORE,
			(Texture::GetGraphSizeX("Resource/Texture/Map/bg_hero_01.png")),
			(Texture::GetGraphSizeY("Resource/Texture/Map/bg_hero_01.png")),
			true
		));

	// 背景2
	obj_mng->Entry(m_pbg2 = new BackGround("Map/BGData/BG2.csv", m_pmap_tip, BG_AFTER,
		(Texture::GetGraphSizeX("Resource/Texture/Map/bg_hero_01.png")),// バグった理由
		(Texture::GetGraphSizeY("Resource/Texture/Map/bg_hero_01.png")),
		false
	));
}


MapManager::~MapManager() {

	// マップデータが入っている場合は削除する
	if (m_pmap_tip != nullptr) {

		// マップの削除
		m_pmap_tip = nullptr;
		delete m_pmap_tip;
	}
}


void MapManager::Update() {

	// nullチェック
	if (m_pmap_tip == nullptr) {
		return;
	}
	if (m_pbg == nullptr) {
		return;
	}

	// マップ関連更新
	m_pmap_tip->Update();
	m_pbg->Update();

}


void MapManager::Draw(){

	// 描画
	m_pbg->Draw();
	m_pmap_tip->Draw();
}


Map MapManager::GetMapInstance()const {
	return *m_pmap_tip;
}


float MapManager::GetMaxMapPos()const {
	return m_pbg->GetMaxMapPos();
}


bool MapManager::IsMaxMapRange()const {
	return m_pbg->IsMaxScroll();
}
