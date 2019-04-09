#include"SeaUrchin.h"

SeaUrchin::SeaUrchin(float x,float y) {
	Init();
	// 生成時に座標を受けとって代入
	m_posx = x;
	m_posy = y;
}

void SeaUrchin::Init() {
	// StateをWaitで初期化
	m_pstate_base = Wait::GetInstance();
	Texture::Load("uni.jpg");
	m_posx = 0;
	m_posy = 0;
	is_dead = false;
}

void SeaUrchin::Update() {
	m_pstate_base->Action();
}

void SeaUrchin::Draw() {
	Texture::Draw2D("uni.jpg", m_posx, m_posy);
}

bool SeaUrchin::GetDeadFlag() {
	return is_dead;
}
