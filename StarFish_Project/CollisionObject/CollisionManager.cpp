#include"CollisionManager.h"
#include"../GameObject/Object/Object.h"
#include"../PrototypeEnemy/PrototypeEnemyManager.h"



CollisionManager::CollisionManager(Player*p1, Player*p2, EnemyManager*e_mng) {

}


void CollisionManager::Collision() {

	
	// プレイヤーとの当たり判定
	ChackHitCircle(m_pp1,m_pp2);

	// 敵と自機の当たり判定
	for (int i = 0; i < e_mng->GetEnemyArraySize(); i++) {
		ChackHitCircle(&e_mng->GetEnemypInstance(i), m_pp1);
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
