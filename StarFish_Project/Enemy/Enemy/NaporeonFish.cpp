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

	m_p_state_base->Action(this);
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

StateId NaporeonFish::CheckChangeState() {

	D3DXVECTOR2 vec1;
	D3DXVECTOR2 vec2;

	// 自身の向きによって三角形のできる位置を左右逆転させる
	if (m_is_left == true) {
		vec1 = { m_pos.x + CHASE_RANGE,m_pos.y - CHASE_RANGE };
		vec2 = { m_pos.x + CHASE_RANGE,m_pos.y + CHASE_RANGE };
	}
	else if (m_is_left == false) {
		vec1 = { m_pos.x - CHASE_RANGE,m_pos.y - CHASE_RANGE };
		vec2 = { m_pos.x - CHASE_RANGE,m_pos.y + CHASE_RANGE };
	}

	// プレイヤーが２機とも範囲にいれば、より近いほうを追跡する
	if (CheckTargetInTheRange(m_pos, vec1, vec2, m_p_player[0]->GetPos()) == true && CheckTargetInTheRange(m_pos, vec1, vec2, m_p_player[1]->GetPos()) == true) {

		// 自身とプレイイヤーの位置の距離を算出
		D3DXVECTOR2 distance1 = CalcDistanceToPlayer(m_p_player[0]->GetPos());
		D3DXVECTOR2 distance2 = CalcDistanceToPlayer(m_p_player[1]->GetPos());

		if (distance1.x < distance2.x) {

			m_anim_change_time = 15;
			m_speed = 3.f;
			m_target_pos = m_p_player[0]->GetPos();
			m_enemy_texture[EnemyTexture::NAPOREONFISH_ATTACK];
			
			return StateId::CHASE_ID;
		}
		else if (distance1.x > distance2.x) {

			m_anim_change_time = 15;
			m_speed = 3.f;
			m_target_pos = m_p_player[1]->GetPos();
			m_enemy_texture[EnemyTexture::NAPOREONFISH_ATTACK];
			
			return StateId::CHASE_ID;
		}
	}
	// プレイヤー１が範囲内のとき
	else if (CheckTargetInTheRange(m_pos, vec1, vec2, m_p_player[0]->GetPos()) == true) {
		m_anim_change_time = 15;
		m_speed = 3.f;
		m_target_pos = m_p_player[0]->GetPos();
		m_enemy_texture[EnemyTexture::NAPOREONFISH_ATTACK];
		
		return StateId::CHASE_ID;
	}
	// プレイヤー２が範囲内のとき
	else if (CheckTargetInTheRange(m_pos, vec1, vec2, m_p_player[1]->GetPos()) == true) {
		m_anim_change_time = 15;
		m_speed = 3.f;
		m_target_pos = m_p_player[1]->GetPos();
		m_enemy_texture[EnemyTexture::NAPOREONFISH_ATTACK];
	
		return StateId::CHASE_ID;
	}
	else {
		m_anim_change_time = 15;
		m_speed = 2.5f;
		m_enemy_texture[EnemyTexture::NAPOREONFISH_MOVE];

		return StateId::PATROL_ID;
	}

	m_anim_change_time = 15;
	m_enemy_texture[EnemyTexture::NAPOREONFISH_MOVE];

	return StateId::WAIT_ID;
}
//―――――――――――――――――――――――――

// ベクトル減算関数
D3DXVECTOR2 NaporeonFish::SubVector(const D3DXVECTOR2& vec1, const D3DXVECTOR2& vec2) {

	D3DXVECTOR2 ret;
	// ベクトル同士の減算
	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;
	
	return ret;
}
//―――――――――――――――――――――――――

// 点と三角形の当たり判定（敵の索敵範囲にプレイヤーが入ったかを判定する）
bool NaporeonFish::CheckTargetInTheRange(D3DXVECTOR2 vecA, D3DXVECTOR2 vecB, D3DXVECTOR2 vecC, D3DXVECTOR2 target_pos) {

	// 外積を求めるために必要な各ベクトル成分を計算
	D3DXVECTOR2 vecAB = SubVector(vecB, vecA);
	D3DXVECTOR2 vecBT = SubVector(target_pos, vecB);

	D3DXVECTOR2 vecBC = SubVector(vecC, vecB);
	D3DXVECTOR2 vecCT = SubVector(target_pos, vecC);

	D3DXVECTOR2 vecCA = SubVector(vecA, vecC);
	D3DXVECTOR2 vecAT = SubVector(target_pos, vecA);

	// 外積を求める
	float crossA = (vecAB.x*vecBT.y) - (vecAB.y*vecBT.x);
	float crossB = (vecBC.x*vecCT.y) - (vecBC.y*vecCT.x);
	float crossC = (vecCA.x*vecAT.y) - (vecCA.y*vecAT.y);

	// 当たり判定
	if ((crossA > 0 && crossB > 0 && crossC > 0) || (crossA < 0 && crossB < 0 && crossC < 0)) {
		return true;
	}

	return false;
}
//―――――――――――――――――――――――――