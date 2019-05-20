#pragma once
#include"../BackGround/BackGround.h"
#include"../../Lib/Window/Window.h"
#include"../../GameObject/Object/Object.h"


/*

マップでは二つの座標があります。

一つ目はスクリーン座標(自分が勝手に付けた名前です)
主に自機などのキャラクターの座標

二つ目はマップ座標(これも自分が勝手につけた名前です)
スクリーン座標をもとにマップチップを動かす座標です。

*/


// チップ情報をまとめる
struct tagMapChip {

	int  m_chip_num;      // チップの種類
	bool m_is_active;     // 存在しているか

	tagMapChip() {
		m_chip_num = 0;
		m_is_active = false;
	}
};


// 各オブジェクトの前方参照
class EnemyManager;
class Player;
class PlayerBase;

// 衝突方向を渡す
enum COL_DIRECTION {
	COL_X,
	COL_Y,
};

// 海マップ
class MapChip : public Object {
public:


	MapChip(Player*star1, Player*star2, EnemyManager*e_mng);


	// 更新関数
	void Update();
	// マップのオブジェクトを生成して描画
	void Draw();

	// Object生成
	void ObjectCreate();
	// Object削除
	void ObjectDestory();
	
	// アクセサ
	//D3DXVECTOR2 GetMapPos()const;
	D3DXVECTOR2 GetMovePos()const;
	// 立っているかどうか
	bool IsStand()const;

	void MapResat(float map_y);

private:


	/* 当たり判定 */
	void MapCollision(D3DXVECTOR2&pos, D3DXVECTOR2&move);
	// 床と当たっているかどうか
	bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y);
	bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y, int &col_chip);
	// 横と縦の衝突後での位置補正
	void NowPosXFixToMapPos(float &pos_x, float &move_x);
	void NowPosYFixToMapPos(float &pos_y, float &move_y);
	// 引っ付き判定
	void StuckCenterChip(float &pos_x,float &pos_y,float &move_x,float &move_y);
	// チップのアクションを起こす関数(ブロックが壊れる、吸いつくなど)
	void ChipAction(D3DXVECTOR2 &pos, D3DXVECTOR2&move_pos, int chip_num, COL_DIRECTION col_d = COL_X);

	/* 描画遷移関係 */
	// 描画範囲に入っているか入っていないか判断する関数

	int DrawLineIsActive(float&pos_y,float&move_y,float up_range,float down_range);
	// スクロールしてもいいかどうか
	bool IsScroll(float &pos_y1, float &pos_y2);
	// 地面に着地する点
	void LandOnTheGround();

	/* マップ操作 */
	// マップ読み込み
	void Load(const std::string&file_name);


	/* マップチップの便利機能 */
	// 位置をマップ座標に変換
	int GetChipCastByPos(const float&pos)const;
	// マップ座標を位置に変換
	float GetChipPosCastByChip(const float &chip_x, const float &chip_y)const;
	// 位置をマップ座標に変換
	int GetChipParam(const float &pos_x, const float&pos_y);

private:

	/* 各定数 */
	const int CHIP_SIZE = 64;                                         // 画像、全てのセルの大きさ
	const int HEIGHT_INTERVAL = 60;                                   // 縦間隔をあけて遷移などをする
	const int MAX_CHIP_NUM_W = BackGround::GRAPH_SCALE_W / CHIP_SIZE; // 画面マップチップの大きさ
	const int MAX_CHIP_NUM_H = BackGround::GRAPH_SCALE_H / CHIP_SIZE; // 画面マップチップの大きさ
	const int MAP_SAET_NUM = 5;                                       // マップシートの数
	// マップ座標に関する定数
	const float INIT_MAP_POS_X = 0.f;
	const float INIT_MAP_POS_Y = 0.f;
	// マップのスクロール遷移ライン定数
	const float SCROLL_RANGE_UP = 100.f;
	const float SCROLL_RANGE_DOWN = 900.f;
	// マップ当たり判定の頂点
	const float HIT_POINT_X = -32.f;
	const float HIT_POINT_Y = -56.f;
	// 縮小
	const float SHRINK_X = 6.f;
	const float SHRINK_Y = 6.f;
	// チップ生成領域
	const int CHIP_RANGE_UP = 19;
	const int CHIP_RANGE_DOWN = 1;

private:

	/* マップチップ関係 */
	tagMapChip m_map[1000][1000] = {};     // 全体マップバッファ
	const char*chip_str[11];               // チップ文字列
	/* マップ座標 */
	D3DXVECTOR2 m_player_pos[2];           // 自機の位置
	D3DXVECTOR2 m_player_move_pos[2];      // 自機の移動ベクトル
	/* マップ描画領域 */
	//D3DXVECTOR2 m_pos;                 // 描画用マップの位置
	D3DXVECTOR2 m_move_pos;            // 描画用マップの位置
	int m_height_map_num;                  // マップデータの高さ
	int m_map_chip_id[1000]={};            // 生成されたらマップチップを保存する
	int m_chip_num;                        // チップの番号
	/* マップ遷移 */
	float m_draw_range_up;                 // 上の描画の範囲
	float m_draw_range_down;               // 後ろの描画の範囲
	float m_scroll_range_up;               // スクロールライン上
	float m_scroll_range_down;             // スクロールライン下
	/* 各オブジェクトの参照 */	   	       
	Player * m_pbase[2];                   // 自機2体                     
	EnemyManager * e_pmng;                 // 敵の状態
	// ジャンプフラグ
	bool m_is_stand;

	// デバッグ用
	int m_py;
	float m_after_pos_y;
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