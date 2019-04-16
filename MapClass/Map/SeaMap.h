﻿#pragma once
#include"BackGround.h"

#include"../Map/BackGround.h"
#include"../Lib/Window/Window.h"
#include"../PosConnector/PosConnecter.h"



// 海マップ
class SeaMap {
public:


	/* 各定数 */

	static constexpr int CHIP_SIZE = 128;                                   // 画像、全てのセルの大きさ
	static constexpr float CHIP_SIZE_F = (float)CHIP_SIZE;                  // float版
	static constexpr int INTERVAL_HEIGHT = 60;                              // 間隔をあけて遷移などをする
	static constexpr int MAP_NUM_X = BackGround::GRAPH_SCALE_W / CHIP_SIZE; // 画面マップチップの大きさ
	static constexpr int MAP_NUM_Y = BackGround::GRAPH_SCALE_H / CHIP_SIZE;	// 画面マップチップの大きさ
	static constexpr int MAP_SAET_NUM = 5;                                  // マップシートの数

	SeaMap();

	// 更新関数(ここに全て書く)
	void Update();

	/* 当たり判定 */

	// 全体の当たり判定
	void MapColider();
	// 当たり判定
	void Collision(float &pos_x, float &pos_y, float *move_x, float *move_y);


	/* マップ操作 */

	
	// マップのオブジェクトを生成して描画
	void MapObjectCreateDraw();
	// 更新や描画,初期化
	void MapInit();
	// マップ読み込み
	void MapLoad(const std::string&file_name);


	/* 各アクセサ(座標の開示) */

	void SetMovePos(D3DXVECTOR2 &pos) {
		m_move_pos = pos;
	}
	void SetPos(D3DXVECTOR2 &pos) {
		m_player_pos = pos;
	}
	D3DXVECTOR2 GetPos() {
		return m_player_pos;
	}
	D3DXVECTOR2 GetMovePos() {
		return m_move_pos;
	}


	/* マップチップの便利機能 */

	template<typename T>
	// マップ座標を一部取り出す
	int GetChipPosCast(const T&pos);
	// 位置をマップ座標に変換
	int GetChipParam(const float &pos_x, const float&pos_y, const int&map_number = 0);
	// マップ座標を位置に変換
	void SetPosParam(const int&pos_x, const int&pos_y, const int &cell, const int&map_number = 0);


	// PosConnectorによる座標変更
	void SetPosConnector(PosConnector*pos_connector);

private:

	/* マップ座標 */

	D3DXVECTOR2 m_player_pos;// 自機の位置
	D3DXVECTOR2 m_chip_pos;  // チップの位置 
	D3DXVECTOR2 m_move_pos;  // 自機の移動ベクトル

	// 描画用マップバッファ
	int m_draw_map[1000][1000] = {};

	/* マップ描画領域 */

	int m_draw_range_begin;  // 描画領域前
	int m_draw_range_end;    // 描画領域後

};



// MEMO
// プレイヤーは実際には動かない
// 代わりに背景が動いて、自機が動いたように見える
//back_pos.y = p_pos.y;

// マップオブジェクト
// 前と後ろと今のマップオブジェクト

// 描画文の最低限のfor分を回す
// 描画と更新は分ける

/*
前シートと今シートと後シートで今いる位置を探し、
今いる自機の位置を探し、描画する範囲を描画する
*/