#pragma once
#include"./BackGround/BackGround.h"
#include"./Lib/Window/Window.h"




class Map {
public:

	static constexpr int CHIP_SIZE = 128;                                   // 画像、全てのセルの大きさ
	static constexpr float CHIP_SIZE_F = (float)CHIP_SIZE;                  // float版
	static constexpr int INTERVAL_HEIGHT = 60;                              // 間隔をあけて遷移などをする
	static constexpr int MAP_NUM_X = BackGround::GRAPH_SCALE_W / CHIP_SIZE; // 画面マップチップの大きさ
	static constexpr int MAP_NUM_Y = BackGround::GRAPH_SCALE_H / CHIP_SIZE;	// 画面マップチップの大きさ
	static constexpr int MAP_SAET_NUM = 5;                                  // マップシートの数

	Map();
	Map(D3DXVECTOR2 init_pos);

	// 全体の当たり判定
	void MapColider();
	// 当たり判定1
	void Colision(float &pos_x,float &pos_y, float *move_x, float *move_y);
	// 当たり判定2
	void MapHitCheck(float x, float y, float *move_x, float *move_y);

	void MapDraw();

	template<typename T>
	int GetChipPosCast(const T&pos);
	int GetChipParam(const float &pos_x, const float&pos_y, const int&map_number=0);
	void SetChipParam(const int&pos_x, const int&pos_y, const int &cell, const int&map_number=0);

	void Update();
	void Draw();
	void MapInit();

	// 今はこれで行くが、いずれインターフェースをしく
	void AddPos(D3DXVECTOR2&pos) {

		m_move_pos.x += pos.x;
		m_move_pos.y += pos.y;
		// 参照先も初期化
		pos.x = pos.y = 0.f;

	}

	void SetMovePos(D3DXVECTOR2 pos) {
		m_move_pos = pos;
	}
	// 自機の今の位置からブロックの座標を調べる
	void SetPos(D3DXVECTOR2 pos) {
		m_player_pos = pos;
	}

	D3DXVECTOR2 GetPos() {
		return m_player_pos;
	}
	D3DXVECTOR2 GetMovePos() {
		return m_move_pos;
	}
	
private:

	D3DXVECTOR2 m_player_pos;// 自機の位置
	D3DXVECTOR2 m_chip_pos;  // チップの位置 
	D3DXVECTOR2 m_move_pos;  // 自機の移動ベクトル


	// 描画用マップバッファ
	int m_draw_map[1000][1000] = {};

	int m_draw_range_begin;
	int m_draw_range_end;
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