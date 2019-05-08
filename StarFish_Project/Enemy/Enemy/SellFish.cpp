#include"SellFish.h"

SellFish::SellFish(float x, float y, bool no_move) {
	m_pos.x = x;
	m_pos.y = y;
	m_no_move = no_move;
	Init();
}
//―――――――――――――――――――――――

void SellFish::Init() {
	m_pstate_base = Wait::GetInstance();
	
	m_speed = 5;
	m_power = 15;			//　攻撃力の値は仮
	m_max_animation = 2;
	m_anim_change_time = 20;
	m_enemy_type = SELLFISH_ID;	

	if (m_pos.x < (WINDOW_W_F / 2)) {
		m_is_left = true;
		m_angle = 180;
	}
	else if (m_pos.x > (WINDOW_W_F / 2)) {
		m_is_left = false;
		m_angle = 0;
	}
}
//―――――――――――――――――――――――

void SellFish::Update() {
	m_pstate_base->Action(this);

	OutScreen();
}
//―――――――――――――――――――――――

void SellFish::Draw() {
	switch (m_stateid) {
	case WAIT_ID:
		m_anim_change_time = 20;
		m_max_animation = 2;

		Texture::Draw2D(
			"Resource/hora_wait.png",
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
			m_angle, 0.5, 0.5,
			true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
			m_animation_num);

		AnimationDraw(m_max_animation, m_anim_change_time);
		break;
	case SIDEMOVE_ID:
		m_anim_change_time = 5;
		m_max_animation = 4;

		Texture::Draw2D(
			"Resource/hora_attack.png",
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y, 
			m_angle, 0.5, 0.5,
			true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
			m_animation_num);

		AnimationDraw(m_max_animation, m_anim_change_time);
		break;
	}
}
//―――――――――――――――――――――――

void SellFish::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――――
