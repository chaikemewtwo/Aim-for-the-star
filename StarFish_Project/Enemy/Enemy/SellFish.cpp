#include"SellFish.h"


SellFish::SellFish(D3DXVECTOR2 pos, MapChip* map_chip, Player* p1, Player* p2,bool no_move) {
	m_pmap = map_chip;
	m_pplayer1 = p1;
	m_pplayer2 = p2;

	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_no_move = no_move;

	m_speed = 5;
	m_power = 15;			
	m_max_animation = 2;
	m_anim_change_time = 20;
	m_enemy_type = SELLFISH_ID;

	// テクスチャ―の登録
	m_texture_list[WAIT_ID][256] = "Resource/Texture/Enemy/hora_wait.png";
	m_texture_list[SIDEMOVE_ID][256] = "Resource/Texture/Enemy/hora_attack.png";

	if (m_pos.x < (WINDOW_W_F / 2)) {
		m_is_left = true;
		m_angle = 180;
		m_center = 1;
	}
	else if (m_pos.x > (WINDOW_W_F / 2)) {
		m_is_left = false;
		m_angle = 0;
		m_center = 0;
	}
}
//―――――――――――――――――――――――

void SellFish::Update() {
	m_pstate_base->Action(this);
	m_texture = m_texture_list[m_stateid][256];

	// 他処理の確認の為にコメントアウト（マージ前に直しておく）
	//m_pos.y += m_pmap->GetMapMovePos().y;

	OutScreen();
}
//―――――――――――――――――――――――

void SellFish::Draw() {
	// 変数の値は遷移時に変更(敵関数内)、Draw2Dは1つでの処理
	/*switch (m_stateid) {
	case WAIT_ID:
		m_anim_change_time = 20;
		m_max_animation = 2;

		Texture::Draw2D(
			m_texture.c_str(),
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
			m_angle, m_center, m_center,
			true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
			m_animation_num
		);
		AnimationDraw(m_max_animation, m_anim_change_time);
		break;

	case ATTACK_READY_ID:
		m_anim_change_time = 10;
		m_max_animation = 2;

		Texture::Draw2D(
			"Resource/Texture/Enemy/hora_ready.png",
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
			m_angle, m_center, m_center,
			true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
			m_animation_num
		);
		AnimationDraw(m_max_animation, m_anim_change_time);
		break;

	case SIDEMOVE_ID:
		m_anim_change_time = 5;
		m_max_animation = 4;

		Texture::Draw2D(
			m_texture.c_str(),
			m_pos.x, m_pos.y,
			TEXTURE_SIZE_X, TEXTURE_SIZE_Y, 
			m_angle, m_center, m_center,
			true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
			m_animation_num
		);
		AnimationDraw(m_max_animation, m_anim_change_time);
		break;
	}*/
	Texture::Draw2D(
		m_texture.c_str(),
		m_pos.x, m_pos.y,
		TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
		m_angle, m_center, m_center,
		true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
		m_animation_num
	);
	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――

StateId SellFish::IsStateChangeCheck() {
	// 今の状態から条件をチェックして遷移するかを判定する
	if (CalcDistance() < 128) {
		m_anim_change_time = 5;
		m_max_animation = 4;
		return SIDEMOVE_ID;
	}
	//else if (CalcDistance() < 256 && PosIsTop() == true) {
	//	m_anim_change_time = 10;
	//	m_max_animation = 2;
	//	return WAIT_ID;
	//}
	return WAIT_ID;
}
//―――――――――――――――――――――――
