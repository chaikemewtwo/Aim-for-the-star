#include"CollisionManager.h"
#include"../GameObject/Object/Object.h"
#include"../Player/Player.h"
#include"../Enemy/Enemy/EnemyManager.h"
#include"CollisionObject.h"
#include"../CollisionObject/CircleCollisionObject.h"



CollisionManager::CollisionManager(Player*p1,Player*p2, EnemyManager*e_mng) {

	m_pplayer[0] = p1;
	m_pplayer[1] = p2;
	m_pe_mng = e_mng;
}


void CollisionManager::Collision() {

	// プレイヤーとの当たり判定
	ChackHitCircle(m_pplayer[0],m_pplayer[1]);

	// 敵と自機の当たり判定
	for (int i = 0; i < PLAYER_NUM; i++) {

		// 敵と自機の当たり判定
		for (int j = 0; j < m_pe_mng->GetEnemyTotal(); j++) {

			if (m_pe_mng->GetEnemyInstance(j) == nullptr) {
				continue;
			}
			else if (m_pplayer[i] == nullptr) {
				continue;
			}

			ChackHitCircle(m_pe_mng->GetEnemyInstance(j),m_pplayer[i]);
		}
	}
}

/* 以下当たり判定 */

// 円の当たり判定
void CollisionManager::ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2) {

	// nullチェック
	if (obj1 == nullptr) {
		return;
	}

	if (obj2 == nullptr) {
		return;
	}

	// 位置を受け取る
	D3DXVECTOR2 pos1 = obj1->GetPos() + obj1->GetOffset();
	D3DXVECTOR2 pos2 = obj2->GetPos() + obj2->GetOffset();

	// obj1とobj2までの距離を出す
	float distance_x = pos1.x - pos2.x;
	float distance_y = pos1.y - pos2.y;

	// 円の当たり判定
	if (distance_x * distance_x + distance_y * distance_y <
		(obj1->GetRadius() + obj2->GetRadius()) * (obj1->GetRadius() + obj2->GetRadius())) {

		// 当たっていた時の判定
		obj1->HitAction(obj2->GetObjectType());
		obj2->HitAction(obj1->GetObjectType());
	}
}