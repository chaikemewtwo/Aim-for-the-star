#include"../Object/GameObject/Object/Object.h"



Object::Object() {
	m_pos.x = m_pos.y = 0.f;
	// 死んだらtrueにする
	m_is_active = false;
	m_current_id = 0;
}

void Object::ObjectIdRedister() {
	m_current_id++;
	m_id_lists.push_back(m_current_id);
}