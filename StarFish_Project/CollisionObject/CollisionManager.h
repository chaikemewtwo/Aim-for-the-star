#pragma once
#include<vector>


// 前方参照
class CollisionObject;      // 衝突オブジェクト
class CircleCollisionObject;// 円衝突オブジェクト
class EnemyManager;         // 敵管理
//class Player;               // 自機
class PlayerManager;

// 当たり判定を行う場所
class CollisionManager{
public:

	// コンストラクタで実体を入れる
	//CollisionManager(Player*m_p1,Player*p2, EnemyManager*e_mng);
	CollisionManager(PlayerManager * p_mng , EnemyManager*e_mng);

	// 当たり判定を行う所
	void Collision();

	// 円の当たり判定
	void ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2);

private:

	// オブジェクトを置く場所
	PlayerManager * m_p_p_mng;
	EnemyManager*m_pe_mng;
};

