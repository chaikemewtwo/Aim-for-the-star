#include"../Object/Object.h"



Object::Object() {

	m_pos.x = m_pos.y = 0.f;
	// 死んだらtrueにする
	m_is_active = false;
	m_id = 0;
	// 生成されたらid登録
	//IdRegistr();
}

void Object::IdRegistr(int id) {

	// 新しいidを登録
	m_id = id;
	// idを加算
	//m_current_id++;
}