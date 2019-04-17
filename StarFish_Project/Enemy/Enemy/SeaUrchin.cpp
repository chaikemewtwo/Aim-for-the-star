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
	//Texture::Load("Resource/uni.png");

	// 変数の初期化
	m_pos.x = 0;
	m_pos.y = 0;
	m_speed = 2;
	m_dead_timer = 60;
	m_change_timer = 0;
	m_is_dead = false;

	// 敵の種類を設定
	m_enemy_type = SeaUrchinId;
}
//―――――――――――――――――――――――――――

// 更新関数
void SeaUrchin::Update() {
	// 現在のState処理を実行
	m_pstate_base->Action(this);

	OutScreen();

	// 仮の遷移　のちにStateないで遷移させる部分
	if (m_change_timer >= 10) {
		ChangeState(VerticalMove::GetInstance());
		m_change_timer = 0;
	}
}
//―――――――――――――――――――――――――――

// 描画関数
void SeaUrchin::Draw() {
	Texture::Draw2D("Resource/uni.jpg", m_pos.x, m_pos.y);
}
//―――――――――――――――――――――――――――

// 遷移関数《要/変更》
void SeaUrchin::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――――――――
