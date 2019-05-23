#pragma once
#include"../BackGround/BackGround.h"


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
class Map : public Object {
public:

	// 画像、全てのセルの大きさ
	static const int CHIP_SIZE = 64;

	Map(Player*star1, Player*star2, EnemyManager*e_mng);

	// 更新と描画
	void Update();
	void Draw();
	void ObjectCreate();    // Object生成
	void ObjectDestory();   // Object削除
	// マップとの当たり判定
	void MapCollision(D3DXVECTOR2&pos, D3DXVECTOR2&move);
	
	/* アクセサ */
	//D3DXVECTOR2 GetMapPos()const;
	D3DXVECTOR2 GetMovePos()const;
	// 立っているかどうか
	bool IsStand()const;
	// 壁に衝突しているかどうかの活動
	bool IsWallCollision()const;
	bool IsWallVerticalCollision()const;
	bool IsWallSideCollision()const;
	bool IsScroll()const;
	// マップの初期化
	void MapResat(float map_y);

private:
	// オブジェクト化する欠点は必要のないオブジェクト
	// 描画を行うチップはオブジェクト化する理由はある。

	/* 当たり判定 */
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
	bool IsScrollLimit(float &pos_y1, float &pos_y2);
	// 地面に着地する点
	void LandOnTheGround();

	/* マップ操作 */
	// マップ読み込み
	void Load(const std::string&file_name);

	// 敵生成群
	void EnemyCreateGather(int x, int y);


	/* マップチップの便利機能 */
	// 位置をマップ座標に変換
	int GetChipCastByPos(const float&pos)const;
	// マップ座標を位置に変換
	float GetChipPosCastByChip(const float &chip_x, const float &chip_y)const;
	// 位置をマップ座標に変換
	int GetChipParam(const float &pos_x, const float&pos_y);

private:

	/* 各定数 */
	const int HEIGHT_INTERVAL = 60;                                   // 縦間隔をあけて遷移などをする
	const int MAX_CHIP_NUM_W = BackGround::GRAPH_SCALE_W / CHIP_SIZE; // 画面マップチップの大きさ
	const int MAX_CHIP_NUM_H = BackGround::GRAPH_SCALE_H / CHIP_SIZE; // 画面マップチップの大きさ
	const int MAP_SAET_NUM = 5;                                       // マップシートの数
	// マップ座標に関する定数
	const float INIT_MAP_POS_X = 0.f;
	const float INIT_MAP_POS_Y = 0.f;
	// マップのスクロール遷移ライン定数
	const float SCROLL_RANGE_UP = 200.f;
	const float SCROLL_RANGE_DOWN = 800.f;
	// マップ当たり判定の頂点
	const float HIT_POINT_X = -32.f;
	const float HIT_POINT_Y = -56.f;
	// 縮小
	const float SHRINK_X = 6.f;
	const float SHRINK_Y = 6.f;
	// チップ生成領域
	const int CHIP_RANGE_UP = 19;
	const int CHIP_RANGE_DOWN = 1;
	// 岩盤の最大チップ数
	static const int MAX_BEDROCK_CHIP = 10;

private:

	/* マップチップ関係 */
	tagMapChip m_map[1000][1000] = {};     // 全体マップバッファ
	const char*chip_str[MAX_BEDROCK_CHIP]; // 岩盤のチップ文字列
	float chip_u[MAX_BEDROCK_CHIP];        // 線を直す為にずらすUV用配列U
	float chip_v[MAX_BEDROCK_CHIP];        // 線を直す為にずらすUV用配列V
	D3DXVECTOR2 bedrock_chip[MAX_BEDROCK_CHIP];// 岩盤チップをずらす座標
	/* マップ座標 */
	D3DXVECTOR2 m_player_pos[2];           // 自機の位置
	D3DXVECTOR2 m_player_move_pos[2];      // 自機の移動ベクトル
	/* マップ描画領域 */
	//D3DXVECTOR2 m_pos;                   // 描画用マップの位置
	D3DXVECTOR2 m_move_pos;                // 描画用マップの位置
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
	bool m_is_stand;                       // 立っているか
	bool m_is_wall_col;                    // 方向関係なく壁衝突しているか
	bool m_is_wall_col_side;               // 横に衝突しているか
	bool m_is_wall_col_vertical;           // 縦に衝突しているか
	bool m_is_scroll;                      // スクロールしているか

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