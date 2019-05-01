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
	m_animation_speed = 20;
	m_enemy_type = SellFishId;	

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
	case WaitId:
		m_animation_speed = 20;
		Texture::Draw2D(
			"hora_wait.png",
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
			m_angle, 0.5, 0.5,
			true, TEXT_PARTITION_NUM2, TEXT_PARTITION_NUM2,
			m_animation_num
		);
		AnimationDraw(TEXT_PARTITION_NUM2, NEED_PARTITION_NUM1, m_animation_speed);
		break;
	case SideMoveId:
		m_animation_speed = 5;
		Texture::Draw2D(
			"hora_attack.png",
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y, 
			m_angle, 0.5, 0.5,
			true, TEXT_PARTITION_NUM2, TEXT_PARTITION_NUM2,
			m_animation_num
		);
		AnimationDraw(TEXT_PARTITION_NUM2, TEXT_PARTITION_NUM2, m_animation_speed);
		break;
	}
}
//―――――――――――――――――――――――

void SellFish::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――――
