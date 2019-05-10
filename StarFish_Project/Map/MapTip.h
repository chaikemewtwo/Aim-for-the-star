#pragma once
#include"BackGround.h"
#include"../Map/BackGround.h"
#include"../Lib/Window/Window.h"
#include"../GameObject/Object/Object.h"


/*

マップでは二つの座標があります。

一つ目はスクリーン座標(自分が勝手に付けた名前です)
主に自機などのキャラクターの座標

二つ目はマップ座標(これも自分が勝手につけた名前です)
スクリーン座標をもとにマップチップを動かす座標です。

*/


// 各オブジェクトの前方参照
class EnemyManager;
class Star1;
class Star2;
class PlayerBase;


// 海マップ
class MapTip : public Object {
public:


	MapTip(Star1*star1,Star2*star2,EnemyManager*e_mng);

	// 更新関数
	void Update();
	// マップのオブジェクトを生成して描画
	void Draw();

	// Object生成
	void ObjectCreate();
	
	/* 当たり判定 */
	void MapColider(int i);

	D3DXVECTOR2 GetMapPos()const;
	D3DXVECTOR2 GetMapMovePos()const;

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

	// 描画範囲に入っているか入っていないか判断する関数
	int DrawLineIsActive(float&pos_y, float&move_y, float up_range, float down_range);

	/* マップ操作 */
	// マップ読み込み
	void Load(const std::string&file_name);

	// 地面に着地する点
	void LandOnTheGround();

	/* マップチップの便利機能 */
	// マップ座標を一部取り出す
	int GetChipPosCast(const float&pos);
	// 位置をマップ座標に変換
	int GetChipParam(const float &pos_x, const float&pos_y, const int&map_number = 0);
	// マップ座標を位置に変換
	void SetPosParam(const int&pos_x, const int&pos_y, const int &cell, const int&map_number = 0);

private:

	/* 各定数 */
	static constexpr int CHIP_SIZE = 64;                                         // 画像、全てのセルの大きさ
	static constexpr int HEIGHT_INTERVAL = 60;                                   // 縦間隔をあけて遷移などをする
	static constexpr int MAX_CHIP_NUM_W = BackGround::GRAPH_SCALE_W / CHIP_SIZE; // 画面マップチップの大きさ
	static constexpr int MAX_CHIP_NUM_H = BackGround::GRAPH_SCALE_H / CHIP_SIZE; // 画面マップチップの大きさ
	static constexpr int MAP_SAET_NUM = 5;                                       // マップシートの数
	// マップ座標に関する定数
	static constexpr float INIT_MAP_POS_X = 0.f;
	static constexpr float INIT_MAP_POS_Y = 0.f;
	// マップのスクロール遷移ライン定数
	static constexpr float SCROLL_RANGE_UP = 300.f;
	static constexpr float SCROLL_RANGE_DOWN = 800.f;
	// マップ当たり判定の頂点
	static constexpr float HIT_POINT_X = -32.f;// -32.f
	static constexpr float HIT_POINT_Y = 0.f;

private:

	/* マップ座標 */
	D3DXVECTOR2 m_obj_pos[2];       // 自機の位置
	D3DXVECTOR2 m_move_pos[2];      // 自機の移動ベクトル
	int m_draw_map[1000][1000] = {};// 描画用マップバッファ
	/* マップ描画領域 */
	D3DXVECTOR2 m_map_pos;          // 描画用マップの位置              
	int m_height_map_num;           // マップデータの高さ
	int m_map_chip_id[1000]={};     // 生成されたらマップチップを保存する
	int m_chip_num;                 // チップの番号
	/* マップ遷移 */
	float m_draw_range_up;          // 上の描画の範囲
	float m_draw_range_down;        // 後ろの描画の範囲
	float m_scroll_range_up;        // スクロールライン上
	float m_scroll_range_down;      // スクロールライン下
	/* 各オブジェクトの参照 */
	PlayerBase * m_pbase[2];        // 自機2体  
	EnemyManager * e_pmng;          // 敵の状態

	// デバッグ用
	int m_py;
	float m_after_pos_y;
	D3DXVECTOR2 m_map_move_pos;// マップ座標の移動ベクトル
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