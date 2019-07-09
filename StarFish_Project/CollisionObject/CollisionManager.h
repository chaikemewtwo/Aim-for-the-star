#pragma once
#include<vector>


/**
* @file CollisionManager.h
* @brief 衝突管理者ファイル
* @author maekawa
*/


// 前方参照
class CollisionObject;      // 衝突オブジェクト
class CircleCollisionObject;// 円衝突オブジェクト
class EnemyManager;         // 敵管理
//class Player;               // 自機
class PlayerManager;

/**
* @brief 衝突管理者クラス
*/
class CollisionManager{
public:

	// コンストラクタで実体を入れる
	/**
	* @brief コンストラクタ
	* @param[out] player1 自機のポインタ1
	* @param[out] player2 自機のポインタ2
	* @param[out] enemy_manager 敵管理のポインタ3
	*/
	CollisionManager(Player*player1,Player*player2, EnemyManager*enemy_manager);


	/**
	* @brief 当たり判定を行う関数
	*/
	CollisionManager(PlayerManager * p_mng , EnemyManager*e_mng);

	// 当たり判定を行う所
	void Collision();


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
	PlayerManager * m_p_p_mng;
	//! 敵管理のポインタ
	EnemyManager*mp_enemy_manager;
};

