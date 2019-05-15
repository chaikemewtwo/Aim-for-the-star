#pragma once
#include"../MapChip/MapChip.h"
#include"../BackGround/BackGround.h"
#include<vector>
#include<memory>




// ここで使うマップを決める。
// Playerインスタンスを持つ。

// 前方参照
class EnemyManager;
class Player;
class MapChip;

// マップ管理
class MapManager {
public:

	// EnemyManagerも入れる
	MapManager(Player*star1,Player*star2, EnemyManager*e_mng);

	~MapManager();

	// 更新と描画
	void Update();
	void Draw();

	// 奥行バージョン
	void AfterUpdate() {
		m_pbg2->Update();
		m_pbg2->Draw();
	}

private:

	MapChip *m_pmap_tip; // マップの選択
	BackGround*m_pbg;     // 背景
	BackGround *m_pbg2;   // 奥行用の背景
};
