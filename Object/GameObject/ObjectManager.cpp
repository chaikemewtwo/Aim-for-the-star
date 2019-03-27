#include"./ObjectManager.h"




void ObjectManager::Update() {
	

	// 管理クラスのアップデート
	for (auto&itr : m_mng_data) {

		// アドレス変換
		itr->Entry();
		itr->Exit();

		// その管理クラスのアップデート
		for (auto&itr : m_obj) {
			(itr)->Update();
		}
	}

	//for (auto&itr : m_obj) {
	//	itr->Update();
	//}
}
