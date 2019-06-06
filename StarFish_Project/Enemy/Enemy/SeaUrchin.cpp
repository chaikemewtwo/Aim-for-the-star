#include"SeaUrchin.h"


//コンストラクタ
SeaUrchin::SeaUrchin(D3DXVECTOR2 pos, Map* map, bool no_move) {

	// マップを受け取る
	m_pmap = map;

	// 所得した座標の登録
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	// no_moveがtrueの場合は動かないウニの生成
	m_no_move = no_move;
	
	m_offset.x = 128.f;
	m_offset.y = 128.f;

	// その他変数の初期化
	m_speed = 2;
	m_power = 5;			
	m_max_animation = 4;
	m_anim_change_time = 20;

	m_enemy_texture = m_texture_list[SEAURCHIN_MOVE];

	// 画面の左右どちらにいるかを判定
	if (m_pos.x < (Window::WIDTH / 2)) {
		m_is_left = true;
	}
	else if (m_pos.x > (Window::WIDTH / 2)) {
		m_is_left = false;
	}
}
//――――――――――――――――――――――――――

// 更新関数
void SeaUrchin::Update() {

	m_pstate_base->Action(this);
	// マップスクロールに合わせた移動処理
	m_pos.y += m_pmap->GetMove().y;

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
		m_animation_count
	);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――――――

StateId SeaUrchin::StateChangeCheck() {

	// 動かないウニならばWaitのまま
	if (m_no_move == true) {
		return WAIT_ID;
	}

	return VERTICALMOVE_ID;
}
//―――――――――――――――――――――――――――
