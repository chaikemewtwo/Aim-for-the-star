#include"./ObjectManager.h"




void ObjectManager::Update() {
	for (auto&itr : m_obj) {
		itr->Update();
	}
}

void ObjectManager::Draw() {
	for (auto&itr : m_obj) {
		itr->Draw();
	}
}