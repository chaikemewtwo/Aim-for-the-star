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
	m_enemy_type = SellFishId;	
}
//―――――――――――――――――――――――

void SellFish::Update() {
	m_pstate_base->Action(this);

	OutScreen();
}
//―――――――――――――――――――――――

void SellFish::Draw() {
	//Texture::Draw2D("", m_pos.x, m_pos.y);
}
//―――――――――――――――――――――――

void SellFish::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――――
