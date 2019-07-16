#pragma once
#include<vector>
#include"../../Player/PlayerManager.h"
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../ChipBase/ChipBase.h"
#include"../MapCollision/MapCollider.h"



/*各座標説明
// =====================
マップ座標 = マップチップを構成する座標
スクリーン座標 = 画面内で生きる座標
// =====================
*/


// ==============================
/**
* @file Map.h
* @brief チップによるMapを構成する
* @author maekawa
*/
// ==============================



// 前方参照
class EnemyManager;
enum CollisionDirectionType;


/**
* @brief チップを構成するマップクラス
*/
class Map{
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
	static constexpr float INIT_SCROLL_RANGE_UP = 400.f;

	//! スクロール範囲下
	static constexpr float INIT_SCROLL_RANGE_DOWN = 800.f;

public:

	/**
	* @brief マップのコンストラクタ
	* @param[out] Player1のポインタ
	* @param[out] Player2のポインタ
	* @param[out] EnemyManagerのポインタ
	* @param[out] ObjectManagerのポインタ
	*/
	Map(EnemyManager*e_mng,ObjectManager*obj_mng);


	/**
	* @brief マップのデストラクタ
	*/
	~Map();


	/**
	* @brief マップチップの初期化
	*/
	void Init();


	/**
	* @brief 更新(override)
	*/
	void Update();


	/**
	* @brief 描画(override)
	*/
	void Draw();


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
	float GetMove()const;


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
	* @brief int 位置をマップ座標に変換(オーバーロード)
	* @return int
	*/
	int GetChipCastByPos(const int&pos)const;


	/**
	* @brief 位置をチップ番号に変換 
	* @return int
	*/
	int GetChipParam(const float pos_x, const float pos_y);


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
	* @brief スクロール位置を返す
	* @return float
	*/
	float GetPos()const;


	/**
	* @brief スクロール位置を代入
	* @param[in] pos
	*/
	void SetPos(const float&pos);


	/**
	* @brief マップのスクロールの初期化セッター
	* @param[in] is_scroll スクロールしているか
	*/
	void SetIsScroll(bool is_scroll);


	/**
	* @brief スクロールする上の範囲を返すゲッター関数
	* @return float スクロールする上の範囲
	*/
	float GetScrollUpMapPosY();


	/**
	* @brief スクロールする下の範囲を返すゲッター関数
	* @return float スクロールする下の範囲
	*/
	float GetScrollDownMapPosY();


	/**
	* @brief マップ当たり判定のゲッター
	*/
	MapCollider *GetMapColliderInstance();


	/**
	* @brief 移動値のセッター
	*/
	void SetScrollMove(const float&move);


	/**
	* @brief 上のマップスクロール線を変えるセッター
	* @param[in] scroll_line_y
	*/
	void SetScrollUpLine(const float &scroll_line_y);


	/**
	* @brief 下のマップスクロール線を変えるセッター
	* @param[in] scroll_line_y
	*/
	void SetScrollDownLine(const float &scroll_line_y);


private:
	

	/**
	* @brief マップ読み込み
	* @param[out] load_file_name
	*/
	void Load(const std::string&load_file_name);


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


	/**
	* @brief 符号変換
	* @param[out] sign_change_num 変換する値
	* @return float 符号変換した値
	*/
	float GetSignChange(float sign_change_num);


	/**
	* @brief 生成と削除を行う関数
	*/
	void CreateAndDestory();


private:

	//! 縦間隔をあけて遷移などをする
	const int HEIGHT_INTERVAL = 60;

	//! チップ生成領域上							  
	const int CHIP_RANGE_UP = 19;

	//! チップ生成領域下
	const int CHIP_RANGE_DOWN = 1;

private:
	
	//! マップを構成するチップリスト
	std::vector<std::vector<ChipBase*>>m_map_chip_list; 

	//! スクロール位置
	float m_scroll_pos;

	//! マップスクロールの動き
	float m_scroll_move;

	//! 最大マップの高さチップサイズ
	int m_max_map_chip_height_size;		

	//! 上のスクロールするマップ位置Y
	float m_scroll_up_map_line;

	//! 下のスクロールするマップ位置Y
	float m_scroll_down_map_line;

	//! スクロールしているか
	bool m_is_scroll;

	//! 最大スクロールか 
	bool m_is_max_scroll;

	//! 衝突方向[自機2体分][xとy]
	CollisionDirectionType collision_dir_type[2][2];

	//! オブジェクト管理
	ObjectManager * m_p_obj_mng;

	//! 当たり判定マップ生成クラス
	MapCollider * m_p_map_collider;

	//! 自機管理のポインタ
	PlayerManager * m_p_p_mng;

	//! 敵管理のポインタ
	EnemyManager *m_p_enemy_manager;
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