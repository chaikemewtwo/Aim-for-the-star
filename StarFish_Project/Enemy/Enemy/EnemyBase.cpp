#include"../../Lib/Window/Window.h"
#include"../EnemyState/EnemyWaitState/EnemyWaitState.h"
#include"EnemyBase.h"

// コンストラクタで共通の変数初期化
EnemyBase::EnemyBase() {

	m_angle = 0.f;
	m_center = 0.5f;

	// 当たり判定の半径
	m_radius = 64.f;
	// 当たり位置の頂点を画像の中心にずらす
	m_hit_vertex_offset.x = 64.f;
	m_hit_vertex_offset.y = 64.f;
	m_delete_timer = 100;
	m_max_animation = 0;
	m_sin_count = 0.f;

	m_p_state_base = Wait::GetInstance();

	// ソートオブジェクトに敵追加
	m_sort_object_type = SortObjectType::ENEMY;

	//  敵画像の登録　//
	// ウニ
	m_texture_list[EnemyTexture::SEAURCHIN_MOVE] = "Resource/Texture/Enemy/uni_move.png";
	// ほら貝
	m_texture_list[EnemyTexture::SELLFISH_WAIT] = "Resource/Texture/Enemy/hora_wait.png";
	m_texture_list[EnemyTexture::SELLFISH_READY] = "Resource/Texture/Enemy/hora_ready.png";
	m_texture_list[EnemyTexture::SELLFISH_ATTACK] = "Resource/Texture/Enemy/hora_attack.png";
	// メガネモチノウオ
	m_texture_list[EnemyTexture::NAPOREONFISH_LEFT_MOVE] = "Resource/Texture/Enemy/megane_move.png";						
	m_texture_list[EnemyTexture::NAPOREONFISH_LEFT_ATTACK] = "Resource/Texture/Enemy/megane_attack.png";
	m_texture_list[EnemyTexture::NAPOREONFISH_RIGHT_MOVE] = "Resource/Texture/Enemy/megane_move_m.png";
	m_texture_list[EnemyTexture::NAPOREONFISH_RIGHT_ATTACK] = "Resource/Texture/Enemy/megane_attack_m.png";
}
//―――――――――――――――――――――

// 引数で指定したStateに遷移
void EnemyBase::ChangeState(StateBase* state) {
	m_p_state_base = state;
}
//―――――――――――――――――――――

void EnemyBase::CheckEnemyActiv() {

	// 画面外に出たら、削除までの時間をカウントダウン
	if (m_pos.y > Window::HEIGHT || m_pos.x<0 || m_pos.x>Window::WIDTH) {

		if (m_delete_timer >= 0) {

			m_delete_timer--;
			if (m_delete_timer <= 0) {
				m_is_active = false;
			}
		}
	}
	// 画面内に戻ったら時間を戻す
	else if (m_pos.y < Window::HEIGHT || m_pos.x>0 || m_pos.x < Window::WIDTH) {
		m_delete_timer = 60;
	}
}
//―――――――――――――――――――――

void EnemyBase::SideMove() {
	if (m_is_left == true) {
		m_pos.x += m_speed;
	}
	else if (m_is_left == false) {
		m_pos.x -= m_speed;
	}
}
//―――――――――――――――――――――

void EnemyBase::VerticalMove() {
	m_pos.y += m_speed;
}
//―――――――――――――――――――――

void EnemyBase::Patrol() {

	// Sin波を計算
	float curve = (float)sinf(D3DX_PI * 2 / SINCURVE_COUNT_MAX * m_sin_count)*m_speed;
	m_sin_count++;
	m_pos.x -= curve;

	// Sin波が1週したらカウントを初期化、向きを左にする
	if (SINCURVE_COUNT_MAX < m_sin_count) {

		m_sin_count = 0;
		m_is_left = true;		
	}
	// Sin波の中間(折り返し)になったら向きを右向きにする
	else if (m_sin_count == SINCURVE_COUNT_MAX / 2) {
		m_is_left = false;
	}
}
//―――――――――――――――――――――

void EnemyBase::Chase() {

	// 索敵範囲に入ったプレイヤーの角度を計算
	float radian = atan2((m_target_pos.y - m_pos.y), (m_target_pos.x - m_pos.x));
	m_pos.x += cosf(radian)*m_speed;
	m_pos.y += sinf(radian)*m_speed;
}
//―――――――――――――――――――――

bool EnemyBase::IsTopPos() {

	if (m_p_p_mng->GetPosRelay(Player::STAR_1).y - m_pos.y > m_pos.y
		&&m_p_p_mng->GetPosRelay(Player::STAR_2).y - m_pos.y > m_pos.y) {
		return true;
	}

	return false;
}
//―――――――――――――――――――――

// 指定されたプレイヤーの位置と自身の位置の距離を計算する
D3DXVECTOR2 EnemyBase::CalcDistanceToPlayer(const D3DXVECTOR2& target_pos) {

	D3DXVECTOR2 distance;

	// Y軸の距離を正の数で求める
	if (IsTopPos() == true) {
		distance.y = target_pos.y - m_pos.y;
	}
	else if (IsTopPos() == false) {
		distance.y = m_pos.y - target_pos.y;
	}

	// X軸の距離を正の数で求める
	if (m_is_left == true) {
		distance.x = target_pos.x - m_pos.x;
	}
	else if (m_is_left == false) {
		distance.x = m_pos.x - target_pos.x;
	}

	return distance;
}
//―――――――――――――――――――――

EnemyBase* EnemyBase::GetInstance() {
	return this;
}
//―――――――――――――――――――――

float EnemyBase::GetSpeed() {
	return m_speed;
}
//―――――――――――――――――――――

bool EnemyBase::IsLeft() {
	return m_is_left;
}
//―――――――――――――――――――――


