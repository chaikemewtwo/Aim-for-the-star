#include"./ObjectManager.h"




void ObjectManager::Update() {
	
	// 更新
	for (auto&itr : m_obj) {
		itr->Update();
	}

	// 描画
	for (auto&itr : m_obj) {
		itr->Draw();
	}
	
}
