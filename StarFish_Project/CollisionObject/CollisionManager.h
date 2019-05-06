#pragma once
#include"CollisionObject.h"
#include"../CollisionObject/CircleCollisionObject.h"
#include<vector>


// enumで形状を返してもいい

const int PLAYER_NUM = 2;

// 敵管理の参照
class EnemyManager;
class Star1;
class Star2;

// 当たり判定を行う場所
class CollisionManager{
public:

	// コンストラクタで実体を入れる
	CollisionManager(Star1*p1,Star2*p2, EnemyManager*e_mng);

	// 当たり判定を行う所
	void Collision();

private:

	// オブジェクトを置く場所
	Star1 * m_star1;
	Star2 * m_star2;
	EnemyManager*m_pe_mng;
};


// 円の当たり判定
void ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2);