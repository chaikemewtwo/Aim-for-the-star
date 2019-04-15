#pragma once
#include"../MapClass/Map/MapManager.h"
#include"../MapClass/PosConnector/PosConnecter.h"
#include"../MapClass/Player/Player.h"



// ゲームシーン
class GameScene {
public:

	GameScene() {
		// 生成
		m_pplayer = new Player;// 試作用に自機を作成
		m_pmap_mng = new MapManager;
	}

	void Update() {

		// 更新
		m_pmap_mng->Update();

		// キャストアップ
		m_pmap_mng->SetPosConnector(m_pplayer);

		// 自機の更新()
		m_pplayer->Update();
	}

	
	void Draw() {
		
		// 描画
		m_pmap_mng->Draw();
		m_pplayer->Draw();
	}

private:

	PosConnector * m_ppos_connector;
	MapManager * m_pmap_mng;
	Player * m_pplayer;

};