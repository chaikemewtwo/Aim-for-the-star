#include"EnemyManager.h"

EnemyManager::EnemyManager() {
	// 初期化
	for (int num = 0; num < Enemy_Max_Num; num++) {
		m_seaurchin[num] = NULL;
	}
}

EnemyManager::~EnemyManager() {
	for (int num = 0; num < Enemy_Max_Num; num++) {
		if (m_seaurchin[num] != NULL) {
			delete m_seaurchin[num];
		}
	}
}

void EnemyManager::Update() {
	Create();
	for (int num = 0; num < Enemy_Max_Num; num++) {
		if (m_seaurchin[num] != NULL) {
			m_seaurchin[num]->Update();
			if (m_seaurchin[num]->GetDeadFlag() == true) {
				delete m_seaurchin[num];
				m_seaurchin[num] = NULL;
			}
		}
	}
}

void EnemyManager::Draw() {
	for (int num = 0; num < Enemy_Max_Num; num++) {
		if (m_seaurchin[num] != NULL) {
			m_seaurchin[num]->Draw();
		}
	}
}

void EnemyManager::Create() {
	for (int num = 0; num < Enemy_Max_Num; num++) {
		if (m_seaurchin[num] == NULL) {
			float y = (rand() % WINDOW_H_INT);
			float x = (rand() % WINDOW_W_INT);
			m_seaurchin[num] = new SeaUrchin(x, y);
		}
	}
}
