#pragma once
#include"CollisionObject.h"
#include"../Player.h"
#include<vector>


// 敵管理の参照
class EnemyManager;

// 当たり判定を行う場所
class CollisionManager{
public:

	// コンストラクタで実体を入れる
	CollisionManager(Player*p1, Player*p2, EnemyManager*e_mng);

	// 当たり判定を行う所
	void Collision();

	// 円の当たり判定
	void ChackHitCircle(CollisionObject*obj1, CollisionObject*obj2, float radius1, float radius2);

private:
	// ここに管理クラスの参照を置く
	Player * m_pp1;
	Player * m_pp2;
	EnemyManager * m_pe_mng;
};
