#pragma once
#include"SeaMap.h"
#include"BackGround.h"
#include<vector>
#include<memory>
#include"../Player/Player.h"


// ここで使うマップを決める。


// マップ管理
class MapManager {
public:

	
	MapManager();

	~MapManager();

	// 位置
	void SetPosConnector(PosConnector*p) {
		
		// 海マップに送る
		m_psea_map->SetPosConnector(p);
		m_pbg->SetPosConnector(p);
	}

	// 更新と描画
	void Update();
	void Draw();

private:

	
	SeaMap *m_psea_map; // マップの選択
	BackGround*m_pbg;     // 背景
};