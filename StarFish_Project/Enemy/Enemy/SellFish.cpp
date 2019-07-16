#include"SellFish.h"


SellFish::SellFish(D3DXVECTOR2 pos, Map* const map, PlayerManager* const p_mng,bool can_move) {

	// マップとプレイヤーを受け取る
	m_p_map = map;
	//m_p_player[0] = p1;
	//m_p_player[1] = p2;
	m_p_player_manager = p_mng;

	// 取得した座標の登録
	m_pos = pos;

	m_can_move = can_move;

	// その他変数の初期化
	m_speed = 5.f;
	m_max_animation = 2;
	m_anim_change_time = 20;

	m_enemy_texture = m_texture_list[EnemyTexture::SELLFISH_WAIT];


	// 生成時にどちらを向いているか
	if (m_pos.x < WINDOW_CENTER_LINE) {
		m_is_left = true;
	}
	else if (m_pos.x > WINDOW_CENTER_LINE) {
		m_is_left = false;
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

	// 左向きと右向きで画像を反転させる(通常は左向き)
	if (m_is_left == true) {
		Texture::Draw2D(
			m_enemy_texture.c_str(),
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
			m_angle, m_center, m_center,
			true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
			m_animation_count,
			0,0,
			Texture::MIRROR
		);
	}
	else if (m_is_left == false) {
		Texture::Draw2D(
			m_enemy_texture.c_str(),
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
			m_angle, m_center, m_center,
			true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
			m_animation_count
		);
	}

	// アニメーションの更新
	AnimationCount(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――

StateId SellFish::CheckChangeState() {

	D3DXVECTOR2 distance1= CalcDistanceToPlayer(m_p_player_manager->GetPosRelay(Player::STAR_1));
	D3DXVECTOR2 distance2= CalcDistanceToPlayer(m_p_player_manager->GetPosRelay(Player::STAR_2));

	// 近距離で、横移動に遷移
	if ((distance1.y < ATTACK_RANGE && distance1.x > 0) || (distance2.y < ATTACK_RANGE && distance2.x > 0)) {

		m_anim_change_time = 5;
		m_max_animation = 4;
		m_enemy_texture = m_texture_list[EnemyTexture::SELLFISH_ATTACK];

		return StateId::SIDEMOVE_ID;

	}
	// 中距離で、画像のみ攻撃前の画像に変更
	else if (distance1.y < ATTACK_READY_RANGE || distance2.y < ATTACK_READY_RANGE) {

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
