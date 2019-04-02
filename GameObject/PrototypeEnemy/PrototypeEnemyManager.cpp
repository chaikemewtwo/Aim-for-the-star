#include"./PrototypeEnemyManager.h"




EnemyManager::EnemyManager() {

	// このように生成する
	enemy1 = new Enemy;
	enemy2 = new Enemy;
}

void EnemyManager::ObjectConnectorEntry(ObjectConnector*cca_mng) {
	
	// 試作です

	// 生成
	if (enemy1 != nullptr) {
		cca_mng->ObjectEntry(*enemy1);
	}

	if (enemy2 != nullptr) {
		cca_mng->ObjectEntry(*enemy2);
	}
		
	// 削除
	if (enemy1 != nullptr) {

		enemy1 = nullptr;
		delete enemy1;
	}
	if (enemy2 != nullptr) {

		enemy2 = nullptr;
		delete enemy2;
	}
	

}

void EnemyManager::Exit() {

}
