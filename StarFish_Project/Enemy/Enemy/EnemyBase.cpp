#include"../../Lib/Window/Window.h"
#include"../State/EnemyWaitState.h"
#include"EnemyBase.h"


EnemyBase::EnemyBase() {

	m_angle = 0;
	m_center = 0.5;

	// 当たり判定の変形を設定
	m_radius = 64.f;
	// 当たり位置の頂点を画像の中心にずらす
	m_hit_vertex_shift.x = 64.f;
	m_hit_vertex_shift.y = 64.f;

	m_delete_timer = 100;
	m_max_animation = 0;
	m_pstate_base = Wait::GetInstance();

	// ソートオブジェクトに敵追加
	m_sort_object = SortObject::ENEMY;

	// 敵画像の登録
	m_texture_list[SEAURCHIN_MOVE] = "Resource/Texture/Enemy/uni_move.png";
	m_texture_list[SELLFISH_WAIT] = "Resource/Texture/Enemy/hora_wait.png";
	m_texture_list[SELLFISH_READY] = "Resource/Texture/Enemy/hora_ready.png";
	m_texture_list[SELLFISH_ATTACK] = "Resource/Texture/Enemy/hora_attack.png";
}
//―――――――――――――――――――――

void EnemyBase::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――

void EnemyBase::OutScreenCheck() {

	// 画面外に出たら、削除までの時間をカウントダウン
	if (m_pos.y > WINDOW_H_F || m_pos.x<0 || m_pos.x>WINDOW_W_F) {

		if (m_delete_timer >= 0) {

			m_delete_timer--;
			if (m_delete_timer <= 0) {
				m_is_active = false;
			}
		}
	}
	// 画面内に戻ったら時間を戻す
	else if (m_pos.y < WINDOW_H_F || m_pos.x>0 || m_pos.x < WINDOW_W_F) {
		m_delete_timer = 60;
	}
}
//―――――――――――――――――――――

D3DXVECTOR2 EnemyBase::CalcDistance() {

	D3DXVECTOR2 player1_distance;
	D3DXVECTOR2 player2_distance;

	// 自身がプレイヤーよりも上にいる場合
	if (IsTopPos()==true) {

		player1_distance.y = m_pplayer1->GetPos().y - m_pos.y;
		player2_distance.y = m_pplayer2->GetPos().y - m_pos.y;
	}
	// 自身がプレイヤーよりも下にいる場合
	else if (IsTopPos()==false) {

		player1_distance.y = m_pos.y - m_pplayer1->GetPos().y;
		player2_distance.y = m_pos.y - m_pplayer2->GetPos().y;
	}


	// 自身が画面左側にいるとき
	if (m_is_left == true) {

		player1_distance.x = m_pplayer1->GetPos().x - m_pos.x;
		player2_distance.x = m_pplayer2->GetPos().x - m_pos.x;
	}
	// 自身が画面右側にいるとき
	else if (m_is_left == false) {

		player1_distance.x = m_pos.x - m_pplayer1->GetPos().x;
		player2_distance.x = m_pos.x - m_pplayer2->GetPos().x;
	}


	// より近いほうの距離を返す
	if (player1_distance.y < player2_distance.y) {
		return player1_distance;
	}

	return player2_distance;
}
//―――――――――――――――――――――

bool EnemyBase::IsTopPos() {

	if (m_pplayer1->GetPos().y > m_pos.y&&m_pplayer2->GetPos().y > m_pos.y) {
		return true;
	}

	return false;
}
//―――――――――――――――――――――

EnemyBase* EnemyBase::GetInstance() {
	return this;
}
//―――――――――――――――――――――

float EnemyBase::GetSpeed() {
	return m_speed;
}

int EnemyBase::GetPower() {
	return m_power;
}

bool EnemyBase::IsLeft() {
	return m_is_left;
}
//―――――――――――――――――――――
