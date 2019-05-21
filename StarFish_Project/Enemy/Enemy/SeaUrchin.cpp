#include"SeaUrchin.h"


//コンストラクタ
SeaUrchin::SeaUrchin(D3DXVECTOR2 pos, MapChip* map_chip, bool no_move) {
	m_pmap = map_chip;

	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_no_move = no_move;

	m_speed = 2;
	m_power = 5;			
	m_max_animation = 4;
	m_anim_change_time = 20;
	m_enemy_texture = m_texture_list[SEAURCHIN_MOVE];

	if (m_pos.x < (WINDOW_W_F / 2)) {
		m_is_left = true;
	}
	else if (m_pos.x > (WINDOW_W_F / 2)) {
		m_is_left = false;
	}
}
//――――――――――――――――――――――――――

// 更新関数
void SeaUrchin::Update() {
	m_pstate_base->Action(this);
	m_pos.y += m_pmap->GetMovePos().y;

	OutScreenCheck();
}
//―――――――――――――――――――――――――――

// 描画関数
void SeaUrchin::Draw() {
	Texture::Draw2D(
		m_enemy_texture.c_str(),
		m_pos.x, m_pos.y,
		TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
		m_angle, 0, 0,
		true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
		m_animation_num
	);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――――――

StateId SeaUrchin::StateChangeCheck() {
	if (m_no_move == true) {
		return WAIT_ID;
	}
	return VERTICALMOVE_ID;
}
//―――――――――――――――――――――――――――
