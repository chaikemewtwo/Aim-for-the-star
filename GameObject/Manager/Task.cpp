#include"../Manager/Task.h"



Task::Task(std::vector<Object*>&object) {
	m_object = &object;
}


void Task::ObjectEntry(Object*obj) {

	if (m_object != nullptr) {
		// オブジェクトを代入
		m_object->emplace_back(obj);
	}

}

