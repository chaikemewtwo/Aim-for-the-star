#pragma once
#include"SeaMap.h"
#include"MapBase.h"
#include"BackGround.h"
#include<vector>
#include<memory>


// ここで使うマップを決める。


// マップ管理
class MapManager {
public:

	MapManager();

	~MapManager();

	void SetPosConnector(PosConnector*p) {
		
	}

	void Update();
	void Draw();

private:

	MapBase *m_pmap_base;         // マップの選択
	BackGround*m_pbg;
};