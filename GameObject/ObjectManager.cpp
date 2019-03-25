#include"./ObjectManager.h"



void ObjectManager::Create() {
	for (auto&itr : m_mng_data) {
		if (itr != nullptr) {
			itr->Create();
		}
	}
}


void ObjectManager::Update() {
	for (auto&itr : m_obj) {

		if (itr != nullptr) {
			itr->Update();
		}
	}
}

void ObjectManager::Draw() {
	for (auto&itr : m_obj) {

		if (itr != nullptr) {
			itr->Draw();
		}
	}
}
