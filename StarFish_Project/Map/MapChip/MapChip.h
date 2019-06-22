#pragma once
#include"../BedRockChip/RockChip.h"
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

	int  chip_num;      // チップの種類
	bool is_active;     // 存在しているか

	MapChip() {
		chip_num = 0;
		is_active = false;
	}
};


// 前方参照
class EnemyManager;
class MapObjectFactory;
class MapCollider;



// 海マップ
class Map : public Object {
public:

	// 画像、全てのセルの大きさ
	static constexpr int CHIP_SIZE = 64;
	// 画面マップチップの大きさ
	static constexpr int MAX_IN_WINDOW_CHIP_NUM_W = ((int)(Window::WIDTH) / CHIP_SIZE);   
	// 画面マップチップの大きさ
	static constexpr int MAX_IN_WINDOW_CHIP_NUM_H = ((int)(Window::HEIGHT) / CHIP_SIZE);  
	// スクロール範囲上
	static constexpr float SCROLL_RANGE_UP = 400.f;
	// スクロール範囲下
	static constexpr float SCROLL_RANGE_DOWN = 800.f;

public:

	Map(Player*star1, Player*star2, EnemyManager*e_mng,ObjectManager*obj_mng);

	// 更新と描画
	void Update();
	void Draw();

	// マップオブジェクトの生成と削除
	void MapObjectCreateWidthLine(int create_line_y);
	void MapObjectDestoryWidthLine(int destory_line_y);

	// マップとの当たり判定
	//bool Collision(D3DXVECTOR2&pos, D3DXVECTOR2&move);
	// スクロール移動値ゲッター
	D3DXVECTOR2 GetMove()const;
	// 高さゲッター
	int GetMaxHeightMapSize()const;
	// 位置をマップ座標に変換
	int GetChipCastByPos(const float&pos)const;
	// 位置をチップ番号に変換
	int GetChipParam(const float pos_x, const float pos_y);
	// スクロールする上の範囲
	float GetScrollRangeUp();
	// スクロールする下の範囲
	float GetScrollRangeDown();

	// 立っているかどうか
	bool IsStand()const;
	// 方向関係なく壁に当たっているか
	bool IsWallCollision()const;     
	// 上の壁に当たっているか
	bool IsWallColUp()const;
	// 下の壁に当たっているか
	bool IsWallColDown()const;
	// 左の壁に当たっているか
	bool IsWallColLeft()const;
	// 右の壁に当たっているか
	bool IsWallColRight()const;

	// スクロールしているか
	bool IsScroll()const;			 
	// 最大スクロールかどうか
	bool IsMaxScroll()const;         
	// マップのスクロールの初期化
	void SetIsScroll(bool is_scroll);

	// チップを選択して生きているかを変更する
	void ActiveChangeChipSelect(int x,int y);
	// チップを選択して生きているか確認する
	bool IsActiveChipSelect(int x, int y);
	// チップを選択してチップ番号取得
	int GetChipNumChipSelect(int x, int y);

private:
	
	//// 床と当たっているかどうか
	//bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y);
	//// 横と縦の衝突後での位置補正
	//void SidePosPullBack(float &pos_x, float &move_x);
	//void VerticalPosPullBack(float &pos_y, float &move_y);
	//
	//// 壁の衝突判定を初期化
	//void InitWallCollision();
	// マップ読み込み
	void Load(const std::string&file_name);
	// 描画範囲に入っているか入っていないか判断する関数
	void Scroll(float *pos_y,float *move_y);
	// 地面に着地する点
	void MaxScroll();
	// 岩生成
	void RockChipCreate(int x, int y);
	// 敵生成
	void EnemyCreate(int x, int y);
	// マップ座標を位置に変換
	float GetChipPosCastByChip(const float &chip_x, const float &chip_y)const;
	// プラスの符号に変換
	void PlusSignChange(float &sign_change_num);
	// 生成と削除
	void CreateAndDestory();
	// 自機との当たり判定とスクロール
	void PlayerCollision(int i);
	// 自機のスクロール
	void PlayerScroll(int i);

	// 引っ付き判定
	//void CenterStuckChip(float &pos_x, float &pos_y, float &move_x, float &move_y);
	
private:

	const int HEIGHT_INTERVAL = 60;                     // 縦間隔をあけて遷移などをする
	const int MAP_SAET_NUM = 5;					        // マップシートの数
	// オブジェクトとマップ当たり判定の頂点位置	
	const D3DXVECTOR2 VERTEX_OFFSET{-32.f,-56.f};       // 当たり位置の大きさ
	// チップの大きさ						    
	const float CHIP_SCALE_X = 6.f;			            // 当たり位置の縮小横
	const float CHIP_SCALE_Y = 6.f;			            // 当たり位置の縮小縦
	// チップ生成領域							  
	const int CHIP_RANGE_UP = 19;				        // 生成領域上
	const int CHIP_RANGE_DOWN = 1;				        // 生成領域下

private:
	
	/* マップチップ関係 */
	std::vector<std::vector<MapChip>>m_map_chip_list; // マップチップの配列

	/* マップ描画領域 */					    
	D3DXVECTOR2 m_move;                        // 描画用マップの位置
	int m_max_height_map_size;                 // マップデータの高さ
							     	           
	/* マップスクロール */		     	           
	float m_draw_range_up;                     // 上の描画の範囲
	float m_draw_range_down;                   // 後ろの描画の範囲
	float m_scroll_range_up;                   // スクロールライン上
	float m_scroll_range_down;                 // スクロールライン下
							     
	/* 各オブジェクトの参照 */   
	Player * m_p_player[2];                    // 自機2体                     
	EnemyManager * m_p_enemy_mng;              // 敵の状態
	ObjectManager * m_p_obj_mng;               // オブジェクト管理
	MapCollider * m_p_map_collision;          // 当たり判定マップ生成クラス
	std::vector<RockChip*>m_rock_chip_list;    // BedRockChipの配列を持つ
	
	/* 各フラグ */			     
	bool m_is_stand;                // 立っているか
	bool m_is_wall_collision;       // 方向関係なく壁衝突しているか
	bool m_is_wall_collision_left;  // 左に衝突しているか
	bool m_is_wall_collision_right; // 右に衝突しているか
	bool m_is_wall_collision_up;    // 上に衝突しているか
	bool m_is_wall_collision_down;  // 下に衝突しているか
	bool m_is_scroll;               // スクロールしているか
	bool m_is_max_scroll;           // 最大スクロールか 
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