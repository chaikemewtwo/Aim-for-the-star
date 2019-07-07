#include"MapManager.h"
#include"../../Player/Player.h"
#include"../MapChip/MapChip.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../MapChip/MapChip.h"
#include"../BackGround/BackGround.h"



MapManager::MapManager(Player*star1, Player*star2, EnemyManager*e_mng, ObjectManager*obj_mng) {

	// nullチェック
	if (star1 == nullptr) {
		return;
	}
	if (star2 == nullptr) {
		return;
	}
	if (e_mng == nullptr) {
		return;
	}
	if (obj_mng == nullptr) {
		return;
	}

	// マップ生成
	m_p_map = new Map(star1, star2, e_mng, obj_mng);

	// 背景生成
	m_p_bg1 = new BackGround(
		// 読み込むテキスト名
		"Map/BGData/BG1.csv",
		// マップ実体
		m_p_map,
		// ソートオブジェクトの型
		BEFORE_BG,
		// 指定したサイズを基準にスクロール
		(Texture::Size::GetGraphSizeX("Resource/Texture/Map/bg_hero_1.png")),
		(Texture::Size::GetGraphSizeY("Resource/Texture/Map/bg_hero_1.png")));

	//m_p_bg2 = new BackGround(
	//	// 読み込むテキスト名
	//	"Map/BGData/BG2.csv",
	//	// マップ実体
	//	m_p_map,
	//	// ソートオブジェクトの型
	//	AFTER_BG,
	//	// 指定したサイズを基準にスクロール
	//	(Texture::Size::GetGraphSizeX("Resource/Texture/Map/bg_hero_1.png")),
	//	(Texture::Size::GetGraphSizeY("Resource/Texture/Map/bg_hero_1.png")));


	// マップ登録
	obj_mng->Entry(m_p_map);
	// 背景1登録
	obj_mng->Entry(m_p_bg1);
	// 背景2
	//obj_mng->Entry(m_p_bg2);

	
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
	//m_p_map->Update();
	//m_p_bg1->Update();
}


void MapManager::Draw(){

}


Map MapManager::GetMapInstance()const {
	return *m_p_map;
}


bool MapManager::IsMaxMapRange()const {
	return m_p_map->IsMaxScroll();
}
