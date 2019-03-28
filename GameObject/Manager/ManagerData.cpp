#include"../Manager/ManagerData.h"



ManagerData::ManagerData(std::vector<Object*>&object) {
	m_object = &object;
}


void ManagerData::ObjectEntry(Object*obj) {

	if (m_object != nullptr) {
		// オブジェクトを代入
		m_object->emplace_back(obj);
	}

}

