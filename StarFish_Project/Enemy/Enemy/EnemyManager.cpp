#include<time.h>
#include"EnemyManager.h"
#include"SeaUrchin.h"
#include"SellFish.h"

EnemyManager::EnemyManager(ObjectManager* obg_mng) {
	m_pobj_mng = obg_mng;
	// ランダム生成のためのシード値設定
	srand((unsigned int)time(nullptr));
}
//――――――――――――――――――――――――――

EnemyManager::~EnemyManager() {
	// 配列に要素が残っているものだけ削除
	for(auto &i:m_enemy_list){
		if (i != nullptr) {
			delete i;
		}
	}
}
//――――――――――――――――――――――――――

// 更新関数
void EnemyManager::Update() {
	// 仮の座標生成(まだObjectManagerで渡せないのでここで座標生成)
	float x = (float)(rand() % (WINDOW_W_INT - 100));
	float y = (float)(rand() % (WINDOW_H_INT - 100));
	Create(x, y);
	
	Delete();
}
//―――――――――――――――――――――――――――

// 描画関数
void EnemyManager::Draw() {
	for (auto i : m_enemy_list) {
		if (i != nullptr) {
			// 各要素の描画処理
			i->Draw();
		}
	}
}
//―――――――――――――――――――――――――――

// 敵生成の関数
void EnemyManager::Create(float x, float y) {
	// 敵の最大数と配列サイズの差分を保存
	int diff = Enemy_Max_Num - m_enemy_list.size();

	// 差分だけ配列を回す
	for (int num = 0; num < diff; num++) {
			// 一定の確率で敵を生成
			if (rand() % 100 == 0) {
				// ランダムに割り出したxyを使用して敵を登録
				m_enemy_list.emplace_back(new SeaUrchin(x, y));
				m_pobj_mng->Entry(m_enemy_list.back());
			}
			else if (rand() % 100 == 5) {
				m_enemy_list.emplace_back(new SeaUrchin(x, y, true));
				m_pobj_mng->Entry(m_enemy_list.back());
			}
			else if (rand() % 100 == 3) {
				m_enemy_list.emplace_back(new SellFish(x, y));
				m_pobj_mng->Entry(m_enemy_list.back());
			}
	}
}
//―――――――――――――――――――――――――――

// 敵削除の関数
void EnemyManager::Delete() {
	// 削除ループ
	for (auto it = m_enemy_list.begin(); it != m_enemy_list.end();) {
		// デッドフラグがtrueであれば、該当の要素を削除
		if ((*it)->GetIsActive() == false) {
			// 生成時に登録されているIdで、Object配列側の要素を指定
			m_pobj_mng->Exit((*it)->GetId());
			it = m_enemy_list.erase(it);
		}
		else {
			++it;
		}
	}
}

//――――――――――――――――――――――――――――

// 生成している敵の総数を返す関数
int EnemyManager::GetEnemyTotal() {
	return m_enemy_list.size();
}
//――――――――――――――――――――――――――――
