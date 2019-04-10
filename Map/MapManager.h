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

	MapManager() {

		m_pbg = new BackGround;
		m_pmap_base = new SeaMap;

		m_pbg->BGLoad("Map");
	}

	~MapManager() {
		// マップデータが入っている場合は削除する
		if (m_pmap_base != nullptr) {

			m_pmap_base = nullptr;
			delete m_pmap_base;
		}
	}


	void Update();

private:

	MapBase *m_pmap_base;         // マップの選択
	BackGround*m_pbg;
};