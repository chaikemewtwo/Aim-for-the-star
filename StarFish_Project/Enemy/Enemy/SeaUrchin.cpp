#include"SeaUrchin.h"

//コンストラクタ
SeaUrchin::SeaUrchin(float x, float y, bool no_move) {
	Init();

	// 生成時に座標を受けとって代入
	m_pos.x = x;
	m_pos.y = y;
	// m_no_moveには基本的にデフォルトfのalseが入る
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

	// 敵の種類を設定
	m_enemy_type = SeaUrchinId;
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
	Texture::Draw2D("Resource/uni.png", m_pos.x, m_pos.y);
}
//―――――――――――――――――――――――――――

// 遷移関数《要/変更》
void SeaUrchin::ChangeState(StateBase* state) {
	m_pstate_base = state;
}
//―――――――――――――――――――――――――――
