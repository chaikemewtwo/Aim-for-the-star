#pragma once
#include"CollisionObject.h"
#include"../CollisionObject/CircleCollisionObject.h"
#include<vector>


// enumで形状を返してもいい

const int PLAYER_NUM = 2;


class EnemyManager; // 敵管理の前方参照
class Player;       // 自機の前方参照


// 当たり判定を行う場所
class CollisionManager{
public:

	// コンストラクタで実体を入れる
	CollisionManager(Player*p1,Player*p2, EnemyManager*e_mng);

	// 当たり判定を行う所
	void Collision();

private:

	// オブジェクトを置く場所
	Player * m_pplayer1;
	Player * m_pplayer2;
	EnemyManager*m_pe_mng;
};


// 円の当たり判定
void ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2);