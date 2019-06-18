#include"NaporeonFish.h"


NaporeonFish::NaporeonFish(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2,bool can_move) {

	// マップとプレイヤーを受け取る
	m_p_map = map;
	m_p_player[0] = p1;
	m_p_player[1] = p2;

	// 取得した座標の登録
	m_pos = pos;

	// その他変数の初期化
	m_speed = 5.f;
	m_max_animation = 4;
	m_anim_change_time = 15;
	m_can_move = can_move;

	m_enemy_texture = m_texture_list[EnemyTexture::NAPOREONFISH_MOVE];

	// 画面の左右どちらにいるかを判定
	if (m_pos.x < WINDOW_CENTER_LINE) {
		m_is_left = true;
	}
	else if (m_pos.x > WINDOW_CENTER_LINE) {
		m_is_left = false;
	}
}
//―――――――――――――――――――――――――

void NaporeonFish::Update() {

	m_pstate_base->Action(this);
	// マップスクロールに合わせた移動処理
	m_pos.y += m_p_map->GetMove().y;

	CheckEnemyActiv();
}
//―――――――――――――――――――――――――

void NaporeonFish::Draw() {

	Texture::Draw2D(
		m_enemy_texture.c_str(),
		m_pos.x, m_pos.y,
		TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
		m_angle, m_center, m_center,
		true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
		m_animation_count
	);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――――

StateId NaporeonFish::StateChangeCheck() {
	

	if (CalcDistance().y < CHASE_RANGE && CalcDistance().x>0 && CalcDistance().x < CHASE_RANGE) {
	
		m_anim_change_time = 15;
		m_speed = 3.f;

		m_enemy_texture[NAPOREONFISH_ATTACK];
	
		return StateId::CHASE_ID;
	}

		m_anim_change_time = 15;
		m_speed = 2.5f;
		
		m_enemy_texture[NAPOREONFISH_MOVE];

		return StateId::PATROL_ID;
}
//―――――――――――――――――――――――――
