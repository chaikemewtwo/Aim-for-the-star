#include"SeaUrchin.h"

//コンストラクタ
SeaUrchin::SeaUrchin(D3DXVECTOR2 pos, bool no_move) {
	Init();

	// 生成時に座標を受けとって代入
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	// m_no_moveには基本的にデフォルトのfalseが入る
	m_no_move = no_move;
}
//――――――――――――――――――――――――――

// 初期化関数
void SeaUrchin::Init() {
	// StateをWaitで初期化
	m_pstate_base = Wait::GetInstance();

	// 変数の初期化
	m_speed = 2;
	m_power = 5;			// 攻撃力は仮の数値
	m_max_animation = 4;
	m_anim_change_time = 20;

	// 敵の種類を設定
	m_enemy_type = SEAURCHIN_ID;

	if (m_pos.x < (WINDOW_W_F / 2)) {
		m_is_left = true;
	}
	else if (m_pos.x > (WINDOW_W_F / 2)) {
		m_is_left = false;
	}
}
//―――――――――――――――――――――――――――

// 更新関数
void SeaUrchin::Update() {
	// 現在のState処理を実行
	m_pstate_base->Action(this);

	OutScreen();
}
//―――――――――――――――――――――――――――

// 描画関数
void SeaUrchin::Draw() {

	Texture::Draw2D(
		"Resource/uni_move.png",
		m_pos.x, m_pos.y,
		TEXTURE_SIZE_X, TEXTURE_SIZE_Y,
		0,0.5f, 0.5f,
		true, TEX_PARTITION_NUM2, TEX_PARTITION_NUM2,
		m_animation_num);

	AnimationDraw(m_max_animation, m_anim_change_time);
}
//―――――――――――――――――――――――――――

// 遷移関数
void SeaUrchin::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――――――――
