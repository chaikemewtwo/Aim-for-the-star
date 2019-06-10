#pragma once
#include"../../Map/BedRockChip/BedRockChip.h"
#include<vector>

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
class ObjectManager;


// 衝突方向を渡す
enum COL_DIRECTION {
	COL_X,
	COL_Y,
};

// プラスの符号に変換
#define PlusSignChange (*(-1))

// 海マップ
class Map : public Object {
public:

	/* 各定数 */
	// 画像、全てのセルの大きさ
	static constexpr int CHIP_SIZE = 64;
	// マップのスクロール遷移ライン定数						   
	static constexpr float SCROLL_RANGE_UP = 400.f;			// スクロール範囲上
	static constexpr float SCROLL_RANGE_DOWN = 800.f;		// スクロール範囲下

	Map(Player*star1, Player*star2, EnemyManager*e_mng,ObjectManager*obj_mng);

	// 更新と描画
	void Update();
	void Draw();

	// マップオブジェクトの生成と削除
	void MapObjectCreate();
	void MapObjectDestory();

	// マップとの当たり判定
	bool Collision(D3DXVECTOR2&pos, D3DXVECTOR2&move);
	
	/* アクセサ */
	//D3DXVECTOR2 GetMapPos()const;
	D3DXVECTOR2 GetMove()const;

	bool IsStand()const;			 // 立っているかどうか
	// 壁に衝突しているかどうかの活動
	bool IsWallCollision()const;     // 方向関係なく壁に当たっているか
	bool IsWallColUp()const;         // 上の壁に当たっているか
	bool IsWallColDown()const;       // 下の壁に当たっているか
	bool IsWallColLeft()const;	     // 左の壁に当たっているか
	bool IsWallColRight()const;	     // 右の壁に当たっているか
	bool IsScroll()const;			 // スクロールしているか
	bool IsMaxScroll()const;         // 最大スクロールかどうか

	// マップの初期化
	void SetMapResetY(float map_y);
	void SetIsScroll(bool is_scroll);

	// スクロールを変更
	void SetScrollRangeUp(float range);
	void SetScrollRangeDown(float range);

private:
	
	/* ---当たり判定--- */

	// 床と当たっているかどうか
	bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y);
	bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y, int &col_chip);
	// 横と縦の衝突後での位置補正
	void SidePosFixToMapPos(float &pos_x, float &move_x);
	void VerticalPosFixToMapPos(float &pos_y, float &move_y);
	// 引っ付き判定
	void CenterStuckChip(float &pos_x,float &pos_y,float &move_x,float &move_y);
	// チップのアクションを起こす関数(ブロックが壊れる、吸いつくなど)
	void ChipAction(D3DXVECTOR2 &pos, D3DXVECTOR2&move_pos, int chip_num, COL_DIRECTION col_d = COL_X);
	// 壁の衝突判定を初期化
	void InitWallCollision();


	/* 描画遷移関係 */

	// 描画範囲に入っているか入っていないか判断する関数
	int Scroll(float&pos_y,float&move_y);
	// 地面に着地する点
	void ScrollMaxMove();

	/* マップ操作 */

	// マップ読み込み
	void Load(const std::string&file_name);
	// 敵生成群
	void EnemyCreateGather(int x, int y, int chip_num);
	// 位置をマップ座標に変換
	int GetChipCastByPos(const float&pos)const;								   
	// マップ座標を位置に変換
	float GetChipPosCastByChip(const float &chip_x, const float &chip_y)const; 
	// 位置をマップ座標に変換
	int GetChipParam(const float &pos_x, const float&pos_y);				   
	
private:

	/* 各定数 */
	const int HEIGHT_INTERVAL = 60;                                 // 縦間隔をあけて遷移などをする
	const int MAX_CHIP_NUM_W = ((int)(Window::WIDTH)/ CHIP_SIZE);   // 画面マップチップの大きさ
	const int MAX_CHIP_NUM_H = ((int)(Window::HEIGHT)/ CHIP_SIZE);  // 画面マップチップの大きさ
	const int MAP_SAET_NUM = 5;								        // マップシートの数
	// オブジェクトとマップ当たり判定の頂点位置				   
	const float HIT_VERTEX_X = -32.f;			 // 当たり位置の大きさ
	const float HIT_VERTEX_Y = -56.f;			 // 当たり位置の大きさ
	// 縮小										    
	const float SHRINK_X = 6.f;					 // 当たり位置の縮小横
	const float SHRINK_Y = 6.f;					 // 当たり位置の縮小縦
	// チップ生成領域							  
	const int CHIP_RANGE_UP = 19;				 // 生成領域上
	const int CHIP_RANGE_DOWN = 1;				 // 生成領域下
	// 岩盤の最大チップ数						       
	static const int MAX_BEDROCK_CHIP = 10;		 // 岩盤チップ数

private:
	
	/* マップチップ関係 */
	//tagMapChip m_map[500][200] = {};           // 全体マップバッファ
	std::vector<std::vector<tagMapChip>>m_map;
	const char*chip_str[MAX_BEDROCK_CHIP];      // 岩盤のチップ文字列
	float chip_u[MAX_BEDROCK_CHIP];             // 線を直す為にずらすUV用配列U
	float chip_v[MAX_BEDROCK_CHIP];             // 線を直す為にずらすUV用配列V
	D3DXVECTOR2 bedrock_chip[MAX_BEDROCK_CHIP]; // 岩盤チップをずらす座標

	/* マップ座標 */

	/* マップ描画領域 */					    
	//D3DXVECTOR2 m_pos;         // 描画用マップの位置
	D3DXVECTOR2 m_move;          // 描画用マップの位置
	int m_height_map_num;        // マップデータの高さ
	int m_map_chip_id[1000]={};  // 生成されたらマップチップを保存する
	int m_chip_num;              // チップの番号
							     
	/* マップ遷移 */		     
	float m_draw_range_up;       // 上の描画の範囲
	float m_draw_range_down;     // 後ろの描画の範囲
	float m_scroll_range_up;     // スクロールライン上
	float m_scroll_range_down;   // スクロールライン下
							     
	/* 各オブジェクトの参照 */   
	Player * m_pbase[2];         // 自機2体                     
	EnemyManager * e_pmng;       // 敵の状態
	ObjectManager * m_pobj_mng;  // オブジェクト管理
							     
	/* 各フラグ */			     
	bool m_is_stand;             // 立っているか
	bool m_is_wall_col[2];       // 方向関係なく壁衝突しているか
	bool m_is_wall_col_left;     // 左に衝突しているか
	bool m_is_wall_col_right;    // 右に衝突しているか
	bool m_is_wall_col_up;       // 上に衝突しているか
	bool m_is_wall_col_down;     // 下に衝突しているか
	bool m_is_scroll;            // スクロールしているか
	bool m_is_max_scroll;        // 最大スクロールか 

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