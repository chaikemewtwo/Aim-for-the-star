#include"CollisionManager.h"
#include"../GameObject/Object/Object.h"
#include"../Player/Star1/Star1.h"
#include"../Player/Star2/Star2.h"
#include"../Enemy/Enemy/EnemyManager.h"


CollisionManager::CollisionManager(Star1*p1,Star2*p2, EnemyManager*e_mng) {

	m_star1 = p1;
	m_star2 = p2;
	m_pe_mng = e_mng;
}


void CollisionManager::Collision() {

	// プレイヤーとの当たり判定
	ChackHitCircle(m_star1,m_star2);

	// 敵と自機の当たり判定
	for (int i = 0; i < PLAYER_NUM; i++) {

		// 敵と自機の当たり判定
		for (int i = 0; i < m_pe_mng->GetEnemyTotal(); i++) {
			ChackHitCircle(&m_pe_mng->GetInstance(i), m_pp[i]);
		}
	}
}

/* 以下当たり判定 */

// 円の当たり判定
void ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2) {
	
	// 位置を受け取る
	D3DXVECTOR2 pos1 = obj1->GetPos();
	D3DXVECTOR2 pos2 = obj2->GetPos();

	// obj1とobj2までの距離を出す
	float a = pos1.x - pos2.x;
	float b = pos1.y - pos2.y;

	// 円の当たり判定
	if (a * a + b * b < obj1->GetRadius() * obj2->GetRadius()) {

		// 当たっていた時の判定
		obj1->HitAction(obj2->GetObjectType());
		obj2->HitAction(obj1->GetObjectType());
	}
}
