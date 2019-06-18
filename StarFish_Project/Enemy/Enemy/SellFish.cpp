#include"SellFish.h"


SellFish::SellFish(D3DXVECTOR2 pos, Map* map, Player* p1, Player* p2,bool can_move) {

	// マップとプレイヤーを受け取る
	m_p_map = map;
	m_p_player[0] = p1;
	m_p_player[1] = p2;

	// 取得した座標の登録
	m_pos = pos;

	m_can_move = can_move;

	// その他変数の初期化
	m_speed = 5.f;
	m_max_animation = 2;
	m_anim_change_time = 20;

	m_enemy_texture = m_texture_list[EnemyTexture::SELLFISH_WAIT];


	// 画面の左右どちらにいるかを判定
	if (m_pos.x < WINDOW_CENTER_LINE) {

		m_is_left = true;
		m_angle = 180;
	}
	else if (m_pos.x > WINDOW_CENTER_LINE) {

		m_is_left = false;
		m_angle = 0;
	}
}
//―――――――――――――――――――――――

void SellFish::Update() {

	m_p_state_base->Action(this);
	// マップスクロールに合わせた移動処理
	m_pos.y += m_p_map->GetMove().y;

	CheckEnemyActiv();
}
//―――――――――――――――――――――――

void SellFish::Draw() {

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
//―――――――――――――――――――――――

StateId SellFish::StateChangeCheck() {

	// 近距離で、横移動に遷移
	if (CalcDistance().y < ATTACK_RANGE && CalcDistance().x>0) {

		m_anim_change_time = 5;
		m_max_animation = 4;
		m_enemy_texture = m_texture_list[EnemyTexture::SELLFISH_ATTACK];

		return StateId::SIDEMOVE_ID;

	}
	// 中距離で、画像のみ攻撃前の画像に変更
	else if (CalcDistance().y < ATTACK_READY_RANGE) {

		m_anim_change_time = 10;
		m_max_animation = 2;
		m_enemy_texture = m_texture_list[EnemyTexture::SELLFISH_READY];

		return StateId::WAIT_ID;
	}

	// それ以外は画像と挙動を待機にする
	m_anim_change_time = 20;
	m_max_animation = 2;
	m_enemy_texture = m_texture_list[EnemyTexture::SELLFISH_WAIT];

	return StateId::WAIT_ID;
}
//―――――――――――――――――――――――
