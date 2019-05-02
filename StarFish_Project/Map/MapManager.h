#pragma once
#include"MapTip.h"
#include"BackGround.h"
#include<vector>
#include<memory>
#include"../Player/Player.h"
#include"MapTip.h"



// ここで使うマップを決める。
// Playerインスタンスを持つ。

// マップ管理
class MapManager {
public:


	MapManager(Player*p,EnemyManager*e_mng);

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

	// 自機のポインタ
	Player*m_pp;
};
