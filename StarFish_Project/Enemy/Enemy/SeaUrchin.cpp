#include"SeaUrchin.h"


//コンストラクタ
SeaUrchin::SeaUrchin(D3DXVECTOR2 pos, Map* map, bool can_move) {

	// マップを受け取る
	m_p_map = map;

	// 所得した座標の登録
	m_pos = pos;

	// can_moveがfalseの場合は動かないウニの生成
	m_can_move = can_move;
	
	m_hit_vertex_offset.x = 128.f;
	m_hit_vertex_offset.y = 128.f;

	// その他変数の初期化
	m_speed = 2.f;
	m_max_animation = 4;
	m_anim_change_time = 20;

	m_enemy_texture = m_texture_list[EnemyTexture::SEAURCHIN_MOVE];

	// 画面の左右どちらにいるかを判定
	if (m_pos.x < WINDOW_CENTER_LINE) {
		m_is_left = true;
	}
	else if (m_pos.x > WINDOW_CENTER_LINE) {
		m_is_left = false;
	}
}
//――――――――――――――――――――――――――

// 更新関数
void SeaUrchin::Update() {

	m_p_state_base->Action(this);
	// マップスクロールに合わせた移動処理
	m_pos.y += m_p_map->GetMove().y;

	CheckEnemyActiv();
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
	AnimationCount(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――――――

StateId SeaUrchin::StateChangeCheck() {

	// 動かないウニならばWaitのまま
	if (m_can_move == false) {
		return StateId::WAIT_ID;
	}

	return StateId::VERTICALMOVE_ID;
}
//―――――――――――――――――――――――――――
