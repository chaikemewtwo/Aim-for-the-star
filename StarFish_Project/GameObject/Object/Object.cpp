#include"../Object/Object.h"



Object::Object() {

	m_pos.x = m_pos.y = 0.f;
	// 死んだらtrueにする
	m_is_active = false;
	m_id = 0;
}
