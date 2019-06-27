#pragma once
#include<vector>
#include"../../Player/Player.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../ChipBase/ChipBase.h"



/*

マップでは二つの座標があります。

一つ目はスクリーン座標(自分が勝手に付けた名前です)
主に自機などのキャラクターの座標

二つ目はマップ座標(これも自分が勝手につけた名前です)
スクリーン座標をもとにマップチップを動かす座標です。

*/

// =====================
/**
* @file Map.h
* @brief チップによるMapを構成する
* @author maekawa
*/
// =====================



// 前方参照
class EnemyManager;
class MapObjectFactory;
class MapCollider;
enum CollisionDirectionType;



/**
* @brief マップクラス
*/
class Map : public Object {
public:
	
	//! チップ間の間隔
	static constexpr float ENTRY_CHIP_INTERVAL_Y = 0.5f;
	//! 画像、全てのセルの大きさ
	static const int CHIP_SIZE = 64;
	//! 画面マップチップの大きさ
	static const int MAX_IN_WINDOW_CHIP_NUM_W = ((int)(Window::WIDTH) / CHIP_SIZE);   
	//! 画面マップチップの大きさ
	static const int MAX_IN_WINDOW_CHIP_NUM_H = ((int)(Window::HEIGHT) / CHIP_SIZE);  
	//! スクロール範囲上
	static constexpr float SCROLL_RANGE_UP = 400.f;
	//! スクロール範囲下
	static constexpr float SCROLL_RANGE_DOWN = 800.f;

public:


	/**
	* @brief マップのコンストラクタ
	* @param[out] Player1のポインタ
	* @param[out] Player2のポインタ
	* @param[out] EnemyManagerのポインタ
	* @param[out] ObjectManagerのポインタ
	*/
	Map(Player*star1, Player*star2, EnemyManager*e_mng,ObjectManager*obj_mng);


	/**
	* @brief マップのデストラクタ
	*/
	~Map();


	/**
	* @brief 更新(override)
	*/
	void Update();


	/**
	* @brief 描画(override)
	*/
	void Draw();

	// マップオブジェクトの生成と削除

	/**
	* @brief マップオブジェクトの生成
	* @param[in] create_line_y 横チップ全てにマップオブジェクトを生成する処理を作成する
	*/
	void MapObjectWidthEntryLine(int create_line_y);


	/**
	* @brief マップオブジェクトの削除
	* @param[in] destory_line_y 横チップ全てにマップオブジェクトを削除する処理を作成する
	*/
	void MapObjectWidthExitLine(int destory_line_y);


	/**
	* @brief スクロール移動値ゲッター
	* @return D3DXVECTOR2
	*/
	D3DXVECTOR2 GetMove()const;


	/**
	* @brief 最大マップチップ高さサイズ
	* @return int
	*/ 
	int GetMaxMapChipHeightSize()const;


	/** 
	* @brief 位置をマップ座標に変換
	* @return int
	*/
	int GetChipCastByPos(const float&pos)const;


	/**
	* @brief 位置をチップ番号に変換 
	* @return int
	*/
	int GetChipParam(const float pos_x, const float pos_y);



	// スクロールする上の範囲
	/**
	* @brief 
	*/
	//float GetScrollRangeUp();
	//// スクロールする下の範囲
	//float GetScrollRangeDown();


	/**
	* @brief スクロールしているか
	* @return bool
	*/
	bool IsScroll()const;


	/**
	* @brief 最大スクロールかどうか
	* @return bool
	*/
	bool IsMaxScroll()const; 


	/**
	* @brief マップのスクロールの初期化セッター
	* @param[in] is_scroll スクロールしているか
	*/
	void SetIsScroll(bool is_scroll);


private:
	

	/**
	* @brief マップ読み込み
	* @param[out] 
	*/
	void Load(const std::string&load_file_name);


	/**
	* @brief スクロールする関数
	* @param[out] screen_pos_y 現在いるスクリーン座標値 
	* @param[out] move_y オブジェクトの移動値
	*/
	void Scroll(float *screen_pos_y,float *move_y);


	/**
	* @brief 最大スクロール関数
	*/
	void MaxScroll();


	/**
	* @brief 岩生成関数
	* @param[in] x チップ座標x
	* @param[in] y チップ座標y
	*/
	void RockChipCreate(int x, int y);


	/**
	* @brief 敵生成関数
	* @param[in] x チップ座標x
	* @param[in] y チップ座標y
	*/
	void EnemyCreate(int x, int y);

 
	/**
	* @brief チップをマップチップ位置に変換
	* @param[out] chip_x チップ座標x
	* @param[out] chip_y チップ座標y
	* @return int マップチップ位置に変換した値
	*/
	int GetChipPosCastByChip(const float chip_x, const float chip_y)const;


	// プラスの符号に変換
	/**
	* @brief プラスの符号に変換
	* @param[out] sign_change_num 変換する値
	* @return float 符号変換した値
	*/
	float GetPlusSignChange(float sign_change_num);


	/**
	* @brief 生成と削除を行う関数
	*/
	void CreateAndDestory();


	/**
	* @brief 自機との当たり判定とスクロール
	* @param[in] player_num 当たりを行う自機番号
	*/
	void PlayerCollision(int player_num);


	/** 
	* @brief 自機のスクロール
	* @param[in] player_num スクロールを行う自機番号
	*/
	void PlayerScroll(int player_num);
	

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
	
	// マップチップの配列
	std::vector<std::vector<ChipBase*>>m_map_chip_list; 
	
	/* マップ描画領域 */					    
	D3DXVECTOR2 m_scroll_move;                 // 描画用マップの位置
	int m_max_map_chip_height_size;            // マップチップ高さサイズ
							     	           
	/* マップスクロール */		     	           
	float m_scroll_range_up;                   // スクロールライン上
	float m_scroll_range_down;                 // スクロールライン下
							     
	/* 各オブジェクトの参照 */   
	Player * m_p_player[2];                    // 自機2体         

	CollisionDirectionType collision_dir_type[2][2];// 衝突方向[自機2体分][xとy]
	EnemyManager * m_p_enemy_mng;              // 敵の状態
	ObjectManager * m_p_obj_mng;               // オブジェクト管理
	MapCollider * mp_map_collider;          // 当たり判定マップ生成クラス
	
	/* 各フラグ */			        
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