#include"../Object/Object.h"



Object::Object() {

	m_pos.x = m_pos.y = 0.f;
	// 死んだらtrueにする
	m_is_active = false;
	m_id = 0;
	m_animation_timer = 0;
	m_animation_num = 0;
}


void Object::AnimationDraw(int max_animation, int anim_cange_time) {
	if (m_animation_timer >= anim_cange_time) {
		m_animation_timer = 0;
		m_animation_num++;
		// 描画する画像番号が分割後の使用枚数を超えたら、番号を初期化
		if (m_animation_num >= max_animation) {
			m_animation_num = 0;
		}
	}
	else {
		m_animation_timer++;
	}
}

/* 各アクセサ */
D3DXVECTOR2 Object::GetPos()const {
	return m_pos;
}

int Object::GetId()const {
	return m_id;
}

bool Object::IsActive()const {
	return m_is_active;
}

void Object::SetPos(const D3DXVECTOR2&pos) {
	m_pos = pos;
}

void Object::SetId(int id) {
	m_id = id;
}
