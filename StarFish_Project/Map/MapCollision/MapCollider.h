#pragma once
#include"../MapChip/MapChip.h"





// 移動方向などを示す
enum DirectionType {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	TOTAL,
};


// 衝突方向を示す
enum CollisionDirectionType {
	NONE_COLLISION,
	UP_COLLISION,
	DOWN_COLLISION,
	RIGHT_COLLISION,
	LEFT_COLLISION,
	TOTAL_COLLISION,
};


// マップ当たり判定クラス
class MapCollider {
public:


	MapCollider(Map*map);

	// マップとの当たり判定
	void Collision(D3DXVECTOR2&pos, D3DXVECTOR2&move,CollisionDirectionType &collision_dir_type_x, CollisionDirectionType &collision_dir_type_y);
	// 床と当たっているかどうか
	bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y);

private:

	const float CHIP_SCALE_X = 6.f;  // 当たり位置の縮小横
	const float CHIP_SCALE_Y = 6.f;  // 当たり位置の縮小縦

private:

	// 横と縦の衝突後での位置補正
	void SidePosPullBack(float &pos_x, float &move_x, CollisionDirectionType &collision_dir_type_x);
	// スクロールによる縦位置を引き戻す処理
	void VerticalPosPullBackByScroll(float &pos_y, float &move_y, CollisionDirectionType &collision_dir_type_y);
	// 縦位置を引き戻す処理
	void VerticalPosPullBack(float &pos_y, float &move_y, CollisionDirectionType &collision_dir_type_y);

	DirectionType GetWidthDirectionType(float direction_num_x);
	DirectionType GetHeightDirectionType(float direction_num_y);

private:

	bool m_is_end_scroll;

	// マップインスタンス
	Map*m_p_map;
};