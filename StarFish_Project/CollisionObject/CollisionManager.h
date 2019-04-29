﻿#pragma once
#include"CollisionObject.h"
#include"../CollisionObject/CircleCollisionObject.h"
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

private:

	// オブジェクトを置く場所
	Player * m_pp1;
	Player * m_pp2;
	EnemyManager*e_mng;
};


// 円の当たり判定
void ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2);