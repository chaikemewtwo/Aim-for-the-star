#pragma once



// ===============================
/**
* @file MapCollision.h
* @brief マップの衝突装置ファイル
* @author maekawa
*/
// ===============================


// 前方参照
class Map;
struct D3DXVECTOR2;


/**
* @enum 移動方向の型列挙体
* @brief 移動方向を示す列挙体
*/
enum MoveDirectionType {
	WIDTH,
	HEIGHT,
	TOTAL_DIR_MOVE,
};


/**
* @enum CollisionDirectionType
* @brief 衝突方向を示す列挙体
*/
enum CollisionDirectionType {
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	TOTAL_DIR_COLLISION,
};



/**
* @brief マップの衝突装置クラス
*/
class MapCollider {
public:

	//! オブジェクトとマップ当たり判定の頂点位置X
	static constexpr float VERTEX_OFFSET_X = -32.f;

	//! オブジェクトとマップ当たり判定の頂点位置Y
	static constexpr float VERTEX_OFFSET_Y = -56.f;

public:


	/**
	* @brief MapColliderのコンストラクタ
	* @param[out] map マップのポインタ
	*/
	MapCollider(Map*map);


	/**
	* @brief マップとの当たり判定
	* @param[out] pos 当たり判定を取る位置
	* @param[out] move 当たり判定を取る移動値
	* @param[out] collision_dir_type_x 移動方向X列挙型
	* @param[out] collision_dir_type_y 移動方向Y列挙型
	*/
	void Collision(
		D3DXVECTOR2&pos,
		D3DXVECTOR2&move,
		CollisionDirectionType &collision_dir_type_x,
		CollisionDirectionType &collision_dir_type_y
	);


	/**
	* @brief スクロール位置を返す
	* @return スクロールの衝突情報を返す
	*/
	CollisionDirectionType GetScrollCollisionDirType();


private:

	//! 衝突チップサイズX
	const float CHIP_SCALE_X = 6.f;

	//! 衝突チップサイズY
	const float CHIP_SCALE_Y = 6.f;

private:


	/**
	* @brief 横位置を前の位置まで引き戻す
	* @param[out] pos_x オブジェクト位置X
	* @param[out] pos_y オブジェクト位置Y
	* @param[out] collision_dir_type_x 衝突方向X列挙体
	*/
	void WidthPosPullBackToPrevPos(float &pos_x, float &move_x, CollisionDirectionType &collision_dir_type_x);


	/**
	* @brief 縦位置を引き戻す処理
	* @param[out] pos_y オブジェクト位置Y
	* @param[out] move_y オブジェクトの移動値Y
	* @param[out] collision_dir_type_y 衝突方向Y列挙体
	*/
	void HeightPosPullBackPrevPos(float &pos_y, float &move_y, CollisionDirectionType &collision_dir_type_y);


	/**
	* @brief X移動値の衝突方向を返す
	* @param[out] move_x X移動値
	* @return CollsionDirectionType 衝突方向
	*/
	CollisionDirectionType GetCollisionDirectionSerchX(const float&move_x)const;


	/**
	* @brief Y移動値の衝突方向を返す
	* @param[out] move_y Y移動値
	* @return CollsionDirectionType 衝突方向
	*/
	CollisionDirectionType GetCollisionDirectionSerchY(const float&move_y)const;


	/**
	* @brief Y座標のマップチップ当たり判定を行う
	* @param[in] up_left 左上頂点
	* @param[in] up_right 右上頂点
	* @param[in] down_left 左下頂点
	* @param[in] down_right 右下頂点
	* @param[out] pos 衝突位置
	* @param[out] move_y 衝突した場合の移動値y
	* @param[out] collision_dir_type_y 衝突方向yの参照
	*/
	bool YVertexHitCheck(
		D3DXVECTOR2 up_left,
		D3DXVECTOR2 up_right,
		D3DXVECTOR2 down_left,
		D3DXVECTOR2 down_right,
		D3DXVECTOR2&pos,
		float&move_y,
		CollisionDirectionType &collision_dir_type_y
	);


	/**
	* @brief Y座標のマップチップ当たり判定を行う
	* @param[in] up_left 左上頂点
	* @param[in] up_right 右上頂点
	* @param[in] down_left 左下頂点
	* @param[in] down_right 右下頂点
	* @param[out] pos 衝突位置
	* @param[out] move_x 衝突した場合の移動値x
	* @param[out] collision_dir_type_x 衝突方向xの参照
	*/
	bool XVertexHitCheck(
		D3DXVECTOR2 up_left,
		D3DXVECTOR2 up_right,
		D3DXVECTOR2 down_left,
		D3DXVECTOR2 down_right,
		D3DXVECTOR2&pos,
		float&move_x,
		CollisionDirectionType &collision_dir_type_x
	);


	/**
	* @brief 床と当たっているかどうか
	* @param[in] pos_x 床とのチップ衝突位置X
	* @param[in] pos_y 床とのチップ衝突位置Y
	* @param[in] move_x 床の位置と衝突しているかの移動値X
	* @param[in] move_y 床の位置と衝突しているかの移動値Y
	* @return bool 壁と衝突したらtrue、していなかったらfalseを返す
	*/
	bool IsWallCollision(float pos_x, float pos_y, float move_x, float move_y);


private:

	//! マップインスタンス
	Map*m_p_map;

	//! スクロールの状態
	CollisionDirectionType m_scroll_dir_y_type;
};