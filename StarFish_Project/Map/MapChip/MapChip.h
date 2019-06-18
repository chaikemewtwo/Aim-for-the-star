#pragma once
#include"../../Map/BedRockChip/BedRockChip.h"
#include<vector>
#include"../../Player/Player.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"

/*

マップでは二つの座標があります。

一つ目はスクリーン座標(自分が勝手に付けた名前です)
主に自機などのキャラクターの座標

二つ目はマップ座標(これも自分が勝手につけた名前です)
スクリーン座標をもとにマップチップを動かす座標です。

*/


// チップ情報をまとめる
struct MapChip {

	int  m_chip_num;      // チップの種類
	bool m_is_active;     // 存在しているか

	MapChip() {
		m_chip_num = 0;
		m_is_active = false;
	}
};


// 前方参照
class EnemyManager;
class MapObjectFactory;


// 壁に衝突した場合の列挙体
enum WallCollisionType {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	TOTAL,
};


// MapChipManager
// 海マップ
class Map : public Object {
public:

	// 画像、全てのセルの大きさ
	static constexpr int CHIP_SIZE = 64;
	// マップのスクロール遷移ライン定数   
	static constexpr float SCROLL_RANGE_UP = 400.f;			// スクロール範囲上
	static constexpr float SCROLL_RANGE_DOWN = 800.f;		// スクロール範囲下

public:

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
	D3DXVECTOR2 GetMove()const;
	int GetMaxHeightMapSize()const;
	// 位置をマップ座標に変換
	int GetChipCastByPos(const float&pos)const;

	bool IsStand()const;			 // 立っているかどうか
	bool IsWallCollision()const;     // 方向関係なく壁に当たっているか
	bool IsWallColUp()const;         // 上の壁に当たっているか
	bool IsWallColDown()const;       // 下の壁に当たっているか
	bool IsWallColLeft()const;	     // 左の壁に当たっているか
	bool IsWallColRight()const;	     // 右の壁に当たっているか
	bool IsScroll()const;			 // スクロールしているか
	bool IsMaxScroll()const;         // 最大スクロールかどうか

	// マップのスクロールの初期化
	void SetIsScroll(bool is_scroll);
	// チップを選択して生きているかを変更する
	void ActiveChangeChipSelect(int x,int y);
	bool IsActiveChipSelect(int x, int y);
	// チップを選択してチップ番号取得
	int GetChipNumChipSelect(int x, int y);

private:
	
	// 床と当たっているかどうか
	bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y);
	// 横と縦の衝突後での位置補正
	void SidePosFixToMapPos(float &pos_x, float &move_x);
	void VerticalPosFixToMapPos(float &pos_y, float &move_y);
	
	// 壁の衝突判定を初期化
	void InitWallCollision();
	// マップ読み込み
	void Load(const std::string&file_name);
	// 描画範囲に入っているか入っていないか判断する関数
	int Scroll(float&pos_y,float&move_y);
	// 地面に着地する点
	void MaxScroll();
	// 岩生成
	void RockChipCreate(int x, int y, int chip_num);
	// 敵生成
	void EnemyCreate(int x, int y, int chip_num);
	// 引っ付き判定
	void CenterStuckChip(float &pos_x, float &pos_y, float &move_x, float &move_y);
			
	// マップ座標を位置に変換
	float GetChipPosCastByChip(const float &chip_x, const float &chip_y)const;
	// 位置をマップ座標に変換
	int GetChipParameter(const float &pos_x, const float&pos_y);		
	// プラスの符号に変換
	void PlusSignChange(float &sign_change_num);
	
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
	const float CHIP_SCALE_X = 6.f;			     // 当たり位置の縮小横
	const float CHIP_SCALE_Y = 6.f;			     // 当たり位置の縮小縦
	// チップ生成領域							  
	const int CHIP_RANGE_UP = 19;				 // 生成領域上
	const int CHIP_RANGE_DOWN = 1;				 // 生成領域下

private:
	
	/* マップチップ関係 */
	std::vector<std::vector<MapChip>>m_map_chip_list;   // マップチップの配列

	/* マップ描画領域 */					    
	D3DXVECTOR2 m_move;          // 描画用マップの位置
	int m_max_height_map_size;   // マップデータの高さ
							     
	/* マップ遷移 */		     
	float m_draw_range_up;       // 上の描画の範囲
	float m_draw_range_down;     // 後ろの描画の範囲
	float m_scroll_range_up;     // スクロールライン上
	float m_scroll_range_down;   // スクロールライン下
							     
	/* 各オブジェクトの参照 */   
	Player * m_p_player[2];                   // 自機2体                     
	EnemyManager * m_p_enemy_mng;             // 敵の状態
	ObjectManager * m_p_obj_mng;              // オブジェクト管理
							     
	/* 各フラグ */			     
	bool m_is_stand;             // 立っているか
	bool m_is_wall_collision;          // 方向関係なく壁衝突しているか
	bool m_is_wall_collision_left;     // 左に衝突しているか
	bool m_is_wall_collision_right;    // 右に衝突しているか
	bool m_is_wall_collision_up;       // 上に衝突しているか
	bool m_is_wall_collision_down;     // 下に衝突しているか
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