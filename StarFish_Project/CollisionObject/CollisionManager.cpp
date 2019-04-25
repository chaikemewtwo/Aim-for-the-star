#include"CollisionManager.h"
#include"../GameObject/Object/Object.h"




CollisionManager::CollisionManager(Player*p1, Player*p2, EnemyManager*e_mng) {

	// 実体を代入
	m_pp1 = p1;
	m_pp2 = p2;
	m_pe_mng = e_mng;
}


void CollisionManager::Collision() {

	// プレイヤーとの当たり判定
	ChackHitCircle(m_pp1,m_pp2,2.f,2.f);
}


/* 以下当たり判定 */

void CollisionManager::ChackHitCircle(CollisionObject*obj1, CollisionObject*obj2,float radius1,float radius2) {
	
	// 位置を受け取る
	D3DXVECTOR2 pos1 = obj1->GetPos();
	D3DXVECTOR2 pos2 = obj2->GetPos();

	// obj1とobj2までの距離を出す
	float a = pos1.x - pos2.x;
	float b = pos1.y - pos2.y;

	// 円の当たり判定
	if (a*a + b * b < radius1 * radius2) {

		// 当たっていた時の判定
		obj1->HitAction();
		obj2->HitAction();
	}
}