#pragma once
#include"MapTip.h"
#include"BackGround.h"
#include<vector>
#include<memory>
#include"../Player/Player.h"
#include"MapTip.h"


// ここで使うマップを決める。


// マップ管理
class MapManager {
public:

	
	MapManager();

	~MapManager();

	// 位置
	void SetpPlayerInstance(Player*player);

	// 更新と描画
	void Update();
	void Draw();

private:

	
	MapTip *m_pmap_tip; // マップの選択
	BackGround*m_pbg;     // 背景
};