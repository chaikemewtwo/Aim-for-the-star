#include"CollisionManager.h"
#include"../GameObject/Object/Object.h"
#include"../Player/Player.h"
#include"../Player/PlayerManager.h"
#include"../Enemy/Enemy/EnemyManager.h"
#include"CollisionObject.h"
#include"../CollisionObject/CircleCollisionObject.h"
#include"../Map/MapManager/MapManager.h"



CollisionManager::CollisionManager(PlayerManager* player_manager, EnemyManager*enemy_manager, MapManager*map_manager) {


	// nullチェック
	if (player_manager == nullptr) {
		return;
	}

	if (enemy_manager == nullptr) {
		return;
	}

	// メンバにインスタンスを設定
	m_p_enemy_manager = enemy_manager;
	m_p_map_manager = map_manager;
	m_p_player_manager = player_manager;
}


void CollisionManager::Update() {

	Collision();
	MapCollision();
}


void CollisionManager::Collision() {

	// 敵と自機の当たり判定
	for (int i = 0; i < Player::MAX_TYPE; i++) {

		// 敵と自機の当たり判定
		for (int j = 0; j < m_p_enemy_manager->GetEnemyTotal(); j++) {

			if (m_p_enemy_manager->GetEnemyInstance(j) == nullptr) {
				continue;
			}
			else if (m_p_player_manager->GetPlayerInstance(i) == nullptr) {
				continue;
			}

			ChackHitCircle(m_p_enemy_manager->GetEnemyInstance(j), m_p_player_manager->GetPlayerInstance(i));
		}
	}
}


void CollisionManager::ChackHitCircle(CircleCollisionObject*obj1, CircleCollisionObject*obj2) {

	// nullチェック
	if (obj1 == nullptr) {
		return;
	}
	if (obj2 == nullptr) {
		return;
	}

	// 位置を受け取る
	D3DXVECTOR2 pos1 = obj1->GetPos() + obj1->GetHitVertexOffset();
	D3DXVECTOR2 pos2 = obj2->GetPos() + obj2->GetHitVertexOffset();

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


void CollisionManager::MapCollision(){


	// 自機とマップの当たり判定
	for (int i = 0; i < Player::MAX; i++){

		// 衝突移動値
		D3DXVECTOR2 collision_move = m_p_player_manager->GetPlayerInstance(i)->GetMove();

		// マップとの当たり判定
		m_p_map_manager->MapCollision(
			m_p_player_manager->GetPlayerInstance(i),
			collision_move,
			m_player_collision_dir_type[i][0],
			m_player_collision_dir_type[i][1]
		);

		// 移動量初期化
		m_p_player_manager->GetPlayerInstance(i)->SetMove(collision_move);
	}
}
