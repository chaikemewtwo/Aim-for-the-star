#pragma once
#include"MapTip.h"
#include"BackGround.h"
#include<vector>
#include<memory>
#include"../Player/PlayerBase/PlayerBase.h"
#include"MapTip.h"


// ここで使うマップを決める。


// マップ管理
class MapManager {
public:

	MapManager();

	~MapManager();

	// 位置
	void SetPlayer(PlayerBase*player) {
		
		// 海マップにセット
		m_pmap_tip->SetPlayer(player);

		// ゲッターで返す
		player->SetPos(m_pmap_tip->GetPos());
		player->SetMovePos(m_pmap_tip->GetMovePos());

		// 背景にセット
		m_pbg->SetPlayer(player);
	}

	// 更新と描画
	void Update();
	void Draw();

private:

	
	MapTip *m_pmap_tip; // マップの選択
	BackGround*m_pbg;     // 背景
};