#pragma once



// ===============================
/**
* @file MapCollision.h
* @brief マップの衝突装置ファイル
* @author maekawa
*/
// ===============================



/**
* @enum DirectionType
* @brief 方向を示すの列挙体
*/
enum DirectionType {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	TOTAL,
};


// マップクラスの前方参照
class Map;


/**
* @brief マップの衝突装置クラス
*/
class MapCollider {
public:


	/**
	* @enum CollisionDirectionType
	* @brief 衝突方向を示す列挙体
	*/
	enum CollisionDirectionType {
		NONE_COLLISION,
		UP_COLLISION,
		DOWN_COLLISION,
		RIGHT_COLLISION,
		LEFT_COLLISION,
		TOTAL_COLLISION,
	};


	/**
	* @brief MapColliderのコンストラクタ
	* @param[out] map マップのポインタ
	*/
	MapCollider(Map*map);


	/**
	* @brief マップとの当たり判定
	* @param[out] pos 当たり判定を取る位置
	* @param[out] move 当たり判定を取る移動値
	* @param[]
	*/
	void Collision(D3DXVECTOR2&pos, D3DXVECTOR2&move,CollisionDirectionType &collision_dir_type_x, CollisionDirectionType &collision_dir_type_y);


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
	void SidePosPullBackToPrevPos(float &pos_x, float &move_x, CollisionDirectionType &collision_dir_type_x);


	/**
	* @brief 縦位置を前の位置まで引き戻す。スクロールによって
	* @param[out] pos_y オブジェクト位置Y
	* @param[out] move_y オブジェクトの移動値Y
	* @param[out] collision_dir_type_y 衝突方向Y列挙体
	*/
	void VerticalScrollPosPullBackPrevPos(float &pos_y, float &move_y, CollisionDirectionType &collision_dir_type_y);


	/**
	* @brief 縦位置を引き戻す処理
	* @param[out] pos_y オブジェクト位置Y
	* @param[out] move_y オブジェクトの移動値Y
	* @param[out] collision_dir_type_y 衝突方向Y列挙体
	*/
	void VerticalPosPullBackPrevPos(float &pos_y, float &move_y, CollisionDirectionType &collision_dir_type_y);


	/**
	* @brief 横の移動方向を受け取り、それに対する列挙体を返す
	* @param[in] direction_num_x 移動方向変数X
	* @return DirectionType 横の移動方向の列挙体
	*/
	DirectionType GetWidthDirectionType(float direction_num_x);


	/**
	* @brief 縦の移動方向を受け取り、それに対する列挙体を返す
	* @param[in] direction_num_y 移動方向変数Y
	* @return DirectionType 縦の移動方向の列挙体
	*/
	DirectionType GetHeightDirectionType(float direction_num_y);

private:

	//! マップインスタンス
	Map*m_p_map;
};