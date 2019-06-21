#pragma once
#include"../MapChip/MapChip.h"



// 壁に衝突した場合の列挙体
enum WallCollisionType {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	TOTAL,
};



// マップ当たり判定クラス
class MapCollision {
public:

	MapCollision(Map*map);

	// マップとの当たり判定
	bool HitChack(D3DXVECTOR2&pos, D3DXVECTOR2&move);
	// 床と当たっているかどうか
	bool IsFloorCollision(float pos_x, float pos_y, float move_x, float move_y);
	
	bool IsStand()const;			 // 立っているかどうか
	bool IsWallCollision()const;     // 方向関係なく壁に当たっているか
	bool IsWallColUp()const;         // 上の壁に当たっているか
	bool IsWallColDown()const;       // 下の壁に当たっているか
	bool IsWallColLeft()const;	     // 左の壁に当たっているか
	bool IsWallColRight()const;	     // 右の壁に当たっているか

private:

	const float CHIP_SCALE_X = 6.f;  // 当たり位置の縮小横
	const float CHIP_SCALE_Y = 6.f;  // 当たり位置の縮小縦

private:

	// 壁の衝突判定を初期化
	void InitWallCollision();
	// 横と縦の衝突後での位置補正
	void SidePosFixToMapPos(float &pos_x, float &move_x);
	void VerticalPosFixToMapPos(float &pos_y, float &move_y);

private:

	bool m_is_stand;                // 立っているか
	bool m_is_wall_collision;       // 方向関係なく壁衝突しているか
	bool m_is_wall_collision_left;  // 左に衝突しているか
	bool m_is_wall_collision_right; // 右に衝突しているか
	bool m_is_wall_collision_up;    // 上に衝突しているか
	bool m_is_wall_collision_down;  // 下に衝突しているか

	// マップインスタンス
	Map*m_p_map;
};