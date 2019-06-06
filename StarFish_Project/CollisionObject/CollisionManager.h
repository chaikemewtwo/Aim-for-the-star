#pragma once
#include<vector>


const int PLAYER_NUM = 2;

// 前方参照
class CollisionObject;      // 衝突オブジェクト
class CircleCollisionObject;// 円衝突オブジェクト
class EnemyManager;         // 敵管理
class Player;               // 自機


// 当たり判定を行う場所
class CollisionManager{
public:

	// コンストラクタで実体を入れる
	CollisionManager(Player*p1,Player*p2, EnemyManager*e_mng);

	// 当たり判定を行う所
	void Collision();

	// 円の当たり判定
	void ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2);

private:

	// オブジェクトを置く場所
	Player * m_pplayer[2];
	EnemyManager*m_pe_mng;
};

