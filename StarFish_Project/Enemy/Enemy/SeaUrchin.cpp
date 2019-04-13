#include"SeaUrchin.h"

//コンストラクタ
SeaUrchin::SeaUrchin(float x,float y) {
	Init();

	// 生成時に座標を受けとって代入
	m_pos.x = x;
	m_pos.y = y;
}
//――――――――――――――――――――――――――

// デストラクタ
void SeaUrchin::Init() {
	// StateをWaitで初期化
	m_pstate_base = Wait::GetInstance();

	// ウニの画像をロード
	Texture::Load("uni.jpg");

	// 変数の初期化
	m_pos.x = 0;
	m_pos.y = 0;
	m_speed = 2;
	m_dead_timer = 60;
	m_change_timer = 0;
	is_dead = false;

	// 敵の種類を設定
	enemy_type = SeaUrchinId;
}
//―――――――――――――――――――――――――――

// 更新関数
void SeaUrchin::Update() {
	// 現在のState処理を実行
	m_pstate_base->Action(this);

	// 画面外に出たら削除までの時間をカウントダウン
	if (m_pos.y > WINDOW_H_F || m_pos.x<0 || m_pos.x>WINDOW_W_F) {
		if (m_dead_timer >= 0) {
			m_dead_timer--;
			// デッドタイムを下回ったらデッドフラグをtrue
			if (m_dead_timer <= 0) {
				is_dead = true;
			}
		}
	}
	// 画面内に戻ったら時間を戻す
	else if (m_pos.y < WINDOW_H_F || m_pos.x > 0 || m_pos.x < WINDOW_W_F) {
		m_dead_timer = 60;
	}

	if (m_change_timer >= 30) {
		ChangeState(new VerticalMove);
		m_change_timer = 0;
	}
}
//―――――――――――――――――――――――――――

// 描画関数
void SeaUrchin::Draw() {
	Texture::Draw2D("uni.jpg", m_pos.x, m_pos.y);
}
//―――――――――――――――――――――――――――

// 遷移関数
void SeaUrchin::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――――――――

// 座標ゲッター・セッター
float SeaUrchin::GetPosX() {
	return m_pos.x;
}

float SeaUrchin::GetPosY() {
	return m_pos.y;
}

float SeaUrchin::SetPosX(float x) {
	m_pos.x = x;
	return m_pos.x;
}

float SeaUrchin::SetPosY(float y) {
	m_pos.y = y;
	return m_pos.y;
}
//―――――――――――――――――――――――――――

// 速度ゲッター
float SeaUrchin::GetSpeed() {
	return m_speed;
}
//―――――――――――――――――――――――――――

// 遷移用タイマーゲッター・セッター
int SeaUrchin::GetChangeTimer() {
	return m_change_timer;
}

int SeaUrchin::SetChangeTimer() {
	m_change_timer++;
	return m_change_timer;
}
//―――――――――――――――――――――――――――

// 削除用タイマーゲッター
int SeaUrchin::GetDeadTimer() {
	return m_dead_timer;
}
//―――――――――――――――――――――――――――

// 削除フラグゲッター
bool SeaUrchin::GetDeadFlag() {
	return is_dead;
}
//―――――――――――――――――――――――――――
