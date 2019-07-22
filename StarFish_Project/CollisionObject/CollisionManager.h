#pragma once
#include<vector>

#include"CollisionObject.h"
#include"../CollisionObject/CircleCollisionObject.h"
#include"../Enemy/Enemy/EnemyManager.h"
#include"../Player/Player.h"
#include"../Map/MapManager/MapManager.h"
#include"../ManagerBase/ManagerBase.h"



// ===================================
/**
* @file CollisionManager.h
* @brief 衝突管理者ファイル
* @author maekawa
*/
// ===================================


// 前方参照
class CollisionObject;       // 衝突オブジェクト
class CircleCollisionObject; // 円衝突オブジェクト
class EnemyManager;          // 敵管理
class PlayerManager;         // 自機管理


/**
* @brief 衝突管理者クラス
*/
class CollisionManager : public ManagerBase{
public:


	/**
	* @brief コンストラクタ
	* @param[out] player1 自機のポインタ1
	* @param[out] player2 自機のポインタ2
	* @param[out] enemy_manager 敵管理のポインタ3
	*/
	CollisionManager(PlayerManager* player_manager, EnemyManager*enemy_manager,MapManager*map_manager);


	/**
	* オーバーライド更新関数
	*/
	void Update();

	/**
	* @brief 当たり判定
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
	
	//! 自機管理のポインタ
	PlayerManager * m_p_player_manager;

	//! 敵管理のポインタ
	EnemyManager * m_p_enemy_manager;

	//! マップの管理者
	MapManager*m_p_map_manager;
};
