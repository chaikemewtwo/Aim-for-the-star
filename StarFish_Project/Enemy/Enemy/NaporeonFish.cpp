#include"NaporeonFish.h"
#include"../State/EnemyWaitState.h"


NaporeonFish::NaporeonFish(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2,bool can_move) {

	// マップとプレイヤーを受け取る
	m_pmap = map;
	m_pplayer1 = p1;
	m_pplayer2 = p2;

	// 取得した座標の登録
	m_pos = pos;

	// その他変数の初期化
	m_speed = 5.f;
	m_power = 15;
	m_center = 0.5f;
	m_max_animation = 4;
	m_anim_change_time = 15;
	//m_change_direction_count_timer = 0;
	m_no_move = can_move;

	m_pstate_base = Wait::GetInstance();

	m_enemy_texture = m_texture_list[NAPOREONFISH_MOVE];

	// 画面の左右どちらにいるかを判定
	if (m_pos.x < (WINDOW_W_F / 2)) {
		m_is_left = true;
		m_angle = 180;
	}
	else if (m_pos.x > (WINDOW_W_F / 2)) {
		m_is_left = false;
		m_angle = 0;
	}
}
//―――――――――――――――――――――――――

void NaporeonFish::Update() {

	m_pstate_base->Action(this);
	// マップスクロールに合わせた移動処理
	m_pos.y += m_pmap->GetMovePos().y;

	OutScreenCheck();
}
//―――――――――――――――――――――――――

void NaporeonFish::Draw() {

	Texture::Draw2D(
		m_enemy_texture.c_str(),
		m_pos.x, m_pos.y,
		TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
		m_angle, m_center, m_center,
		true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
		m_animation_num
	);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――――

StateId NaporeonFish::StateChangeCheck() {
	

	if (CalcDistance().y < 200 && CalcDistance().x>0 && CalcDistance().x < 200) {
	
		m_anim_change_time = 15;
		m_speed = 3.f;

		m_enemy_texture[NAPOREONFISH_ATTACK];
	
		return CHASE_ID;
	}
	//else{

		m_anim_change_time = 15;
		m_speed = 2.5f;
		
		m_enemy_texture[NAPOREONFISH_MOVE];

		return PATROL_ID;
	//}
}
//―――――――――――――――――――――――――
