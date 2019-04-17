#include"MapManager.h"





MapManager::MapManager() {
	
	// 生成
	m_pbg = new BackGround;
	m_pmap_tip = new MapTip;

	//m_pbg->BGLoad("Map");
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
	//m_pmap_tip->Update();
	m_pbg->Update();
}

void MapManager::Draw() {

	// 描画
	m_pbg->Draw();
	m_pmap_tip->Draw();
}

void MapManager::SetpPlayerInstance(Player*player) {

	// 仮の位置と移動位置を入れる
	//D3DXVECTOR2 prov_pos = player->GetPosition();
	//D3DXVECTOR2 prov_move_pos = player->GetPMovePos();

	// 背景を先にしないと更新されない時があった
	// マップ先で移動ベクトルが初期化されていた。
	
	// 海マップにセット
	m_pmap_tip->SetpPlayerInstance(player);
	// 背景にセット
	m_pbg->SetpPlayerPos(player);
	

	// ゲッターで返す
	//player->SetPosition(prov_pos);
	//player->SetPMovePos(prov_move_pos);

}
