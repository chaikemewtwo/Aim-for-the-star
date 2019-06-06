#include"SellFish.h"


SellFish::SellFish(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2,bool no_move) {

	// マップとプレイヤーを受け取る
	m_pmap = map;
	m_pplayer1 = p1;
	m_pplayer2 = p2;

	// 取得した座標の登録
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_no_move = no_move;

	// その他変数の初期化
	m_speed = 5;
	m_power = 15;			
	m_max_animation = 2;
	m_anim_change_time = 20;

	m_enemy_texture = m_texture_list[SELLFISH_WAIT];


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
//―――――――――――――――――――――――

void SellFish::Update() {

	m_pstate_base->Action(this);
	// マップスクロールに合わせた移動処理
	m_pos.y += m_pmap->GetMove().y;

	OutScreenCheck();
}
//―――――――――――――――――――――――

void SellFish::Draw() {

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
//―――――――――――――――――――――――

StateId SellFish::StateChangeCheck() {

	// 近距離で、横移動に遷移
	if (CalcDistance().y < 200 && CalcDistance().x>0) {

		m_anim_change_time = 5;
		m_max_animation = 4;
		m_enemy_texture = m_texture_list[SELLFISH_ATTACK];

		return SIDEMOVE_ID;

	}
	// 中距離で画像のみ、攻撃前の画像に変更
	else if (CalcDistance().y < 350) {

		m_anim_change_time = 10;
		m_max_animation = 2;
		m_enemy_texture = m_texture_list[SELLFISH_READY];

		return WAIT_ID;
	}

	m_anim_change_time = 20;
	m_max_animation = 2;
	m_enemy_texture = m_texture_list[SELLFISH_WAIT];

	return WAIT_ID;
}
//―――――――――――――――――――――――
