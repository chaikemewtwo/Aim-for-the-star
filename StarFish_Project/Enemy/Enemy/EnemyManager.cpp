#include"EnemyManager.h"

EnemyManager::EnemyManager() {
	// 初期化
	for (int num = 0; num < Enemy_Max_Num; num++) {
		seaurchin[num] = NULL;
	}
}

EnemyManager::~EnemyManager() {
	for (int num = 0; num < Enemy_Max_Num; num++) {
		delete seaurchin[num];
	}
}

void EnemyManager::Update() {
	Create();
	for (int num = 0; num < Enemy_Max_Num; num++) {
		if (seaurchin[num] != NULL) {
			seaurchin[num]->Update();
			if (seaurchin[num]->is_dead == true) {
				delete seaurchin[num];
				seaurchin[num] = NULL;
			}
		}
	}
}

void EnemyManager::Draw() {
	for (int num = 0; num < Enemy_Max_Num; num++) {
		if (seaurchin[num] != NULL) {
			seaurchin[num]->Draw();
		}
	}
}

void EnemyManager::Create() {
	for (int num = 0; num < Enemy_Max_Num; num++) {
		if (seaurchin[num] == NULL) {
			float y = (rand() % WINDOW_H_INT);
			float x = (rand() % WINDOW_W_INT);
			seaurchin[num] = new SeaUrchin(x, y);
		}
	}
}
