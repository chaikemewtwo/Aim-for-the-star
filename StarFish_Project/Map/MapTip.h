#pragma once
#include"BackGround.h"

#include"../Map/BackGround.h"
#include"../Lib/Window/Window.h"
#include"../PosConnector/CollisionObject.h"


class EnemyManager;

// 海マップ
class MapTip {
public:


	/* 各定数 */

	static constexpr int CHIP_SIZE = 64;                                    // 画像、全てのセルの大きさ
	static constexpr float CHIP_SIZE_F = (float)CHIP_SIZE;                  // float版
	static constexpr int HEIGHT_INTERVAL = 60;                              // 縦間隔をあけて遷移などをする
	static constexpr int MAP_NUM_X = BackGround::GRAPH_SCALE_W / CHIP_SIZE; // 画面マップチップの大きさ
	static constexpr int MAP_NUM_Y = BackGround::GRAPH_SCALE_H / CHIP_SIZE;	// 画面マップチップの大きさ
	static constexpr int MAP_SAET_NUM = 5;                                  // マップシートの数

	MapTip(Player*p,EnemyManager*e_mng);

	// 更新関数
	void Update();

	// マップのオブジェクトを生成して描画
	void Draw();

	// Object生成
	void Create();
	
	/* 当たり判定 */

	// 全体の当たり判定
	void MapColider();
	

	/* 各アクセサ(座標のプロパティ) */

	void SetMovePos(D3DXVECTOR2&pos) {
		m_move_pos = pos;
	}
	void SetPos(D3DXVECTOR2&pos) {
		m_obj_pos = pos;
	}
	D3DXVECTOR2 GetPos() {
		return m_obj_pos;
	}
	D3DXVECTOR2 GetMovePos() {
		return m_move_pos;
	}


private:

	// 方角
	enum Direction {
		NORTH,
		SOUTH,
		EAST,
		WEST,
		MAX,
	};

	// マップチップの当たり判定
	void Collision(float &pos_x, float &pos_y, float *move_x, float *move_y);

	// 移動ベクトルが加算されてる方角を知る
	MapTip::Direction GetMoveDirection(D3DXVECTOR2&move_pos);


	/* マップ操作 */


	// マップ読み込み
	void Load(const std::string&file_name);


	/* マップチップの便利機能 */


	// マップ座標を一部取り出す
	int GetChipPosCast(const float&pos);
	// 位置をマップ座標に変換
	int GetChipParam(const float &pos_x, const float&pos_y, const int&map_number = 0);
	// マップ座標を位置に変換
	void SetPosParam(const int&pos_x, const int&pos_y, const int &cell, const int&map_number = 0);

private:


	/* マップ座標 */

	D3DXVECTOR2 m_obj_pos;   // 自機の位置
	D3DXVECTOR2 m_move_pos;  // 自機の移動ベクトル

	// 描画用マップバッファ
	int m_draw_map[1000][1000] = {};


	/* マップ描画領域 */

	int m_height_map_num;    // マップデータの高さ

	int m_map_chip_id[1000]={}; // 生成されたらマップチップを保存する
	int m_id;                // 最新id

	Player*m_pp;             // 自機の参照
	EnemyManager * e_pmng;   // 敵の状態
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