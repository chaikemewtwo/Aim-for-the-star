#pragma once
#include"MapTip.h"
#include"BackGround.h"
#include<vector>
#include<memory>
#include"MapTip.h"



// ここで使うマップを決める。
// Playerインスタンスを持つ。

// 前方参照
class EnemyManager;
class Star1;
class Star2;

// マップ管理
class MapManager {
public:

	// EnemyManagerも入れる
	MapManager(Star1*star1, Star2*star2, EnemyManager*e_mng);

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

	MapTip *m_pmap_tip; // マップの選択
	BackGround*m_pbg;     // 背景
	BackGround *m_pbg2;   // 奥行用の背景
};
