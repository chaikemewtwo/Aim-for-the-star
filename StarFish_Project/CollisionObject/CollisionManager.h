#pragma once
#include<vector>

#include"CollisionObject.h"
#include"../CollisionObject/CircleCollisionObject.h"
#include"../Enemy/Enemy/EnemyManager.h"
#include"../Player/Player.h"
#include"../Map/MapManager/MapManager.h"



// ===================================
/**
* @file CollisionManager.h
* @brief 衝突管理者ファイル
* @author maekawa
*/
// ===================================


const int XY = 2;


/**
* @brief 衝突管理者クラス
*/
class CollisionManager{
public:


	/**
	* @brief コンストラクタ
	* @param[out] player1 自機のポインタ1
	* @param[out] player2 自機のポインタ2
	* @param[out] enemy_manager 敵管理のポインタ3
	*/
	CollisionManager(Player*player1,Player*player2, EnemyManager*enemy_manager,MapManager*map);


	/**
	* @brief 当たり判定を行う関数
	*/
	void Collision();


	/**
	* @brief マップとの当たり判定を行う関数
	*/
	void MapCollision();


	/**
	* @brief 円と円の当たり判定
	* @param[out] circle_collision_object1 円衝突オブジェクト1
	* @param[out] circle_collision_object2 円衝突オブジェクト2
	*/
	void ChackHitCircle(
		CircleCollisionObject*circle_collision_object1,
		CircleCollisionObject*circle_collision_object2
	);


private:

	//! 自機1,2のポインタ
	Player * m_p_player[Player::MAX];

	//! 敵管理のポインタ
	EnemyManager*m_p_enemy_manager;

	//! マップの管理者
	MapManager*m_p_map_manager;

	//! 自機の当たり方向の型
	CollisionDirectionType m_player_collision_dir_type[Player::MAX][XY];
};
