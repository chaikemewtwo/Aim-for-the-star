#include"../Object/Object.h"



Object::Object() {

	m_pos.x = m_pos.y = 0.f;
	// 死んだらtrueにする
	m_is_active = false;
	m_id = 0;
}


void Object::AnimationDraw(int textur_x, int textur_y, int anim_speed) {
	if (m_animation_timer >= anim_speed) {
		m_animation_timer = 0;
		m_animation_num++;
		if (m_animation_num >= (textur_x * textur_y)) {
			m_animation_num = 0;
		}
	}
	else {
		m_animation_timer++;
	}
}
