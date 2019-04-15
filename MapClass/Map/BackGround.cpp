#include"BackGround.h"



// コンストラクタ
BackGround::BackGround() {

	m_pos.x = m_pos.y = 0.f;

	m_pback_str[0] = "Texture/bg_hero_01.png";
	m_pback_str[1] = "Texture/bg_hero_02.png";
	m_pback_str[2] = "Texture/bg_hero_02.png";
	m_pback_str[3] = "Texture/bg_hero_02.png";
	m_pback_str[4] = "Texture/bg_hero_02.png";

	// 最初の背景の位置
	m_pos.x = 50.f;
	m_pos.y = 0.f;

	// 今自機がいる場所
	m_now_position = 0;

	// 画像の位置
	m_now_graph = 0;
	m_next_graph = 1;

}


// 背景スクロール
void BackGround::Scroll() {


	// 画面遷移基準
	float screen_up = SCREEN_DIFFERENCE - GRAPH_SCALE_H;
	float screen_down = -SCREEN_DIFFERENCE + GRAPH_SCALE_H;

	if (m_now_graph == 2) {
		m_now_graph = 2;
	}

	// 前にずれているか後ろにずれているかを判断して画像をずらす

	// MEMO 背景は-50 * -50を頂点に描画するので前は50piずらす必要はない
	// 前
	if (-m_pos.y - BG_MOVE_LINE <= (-GRAPH_SCALE_H) * m_now_graph) {
		m_next_graph = m_now_graph + 1;
	}

	// 前に進んでいる今
	if (-m_pos.y - BG_MOVE_LINE <= (-GRAPH_SCALE_H) * m_next_graph) {
		m_now_graph = m_next_graph + 1;
	}

	// 下に背景遷移ラインを貼る
	if ((-m_pos.y + GRAPH_SCALE_H - SCREEN_DIFFERENCE) + BG_MOVE_LINE
		>= (-GRAPH_SCALE_H) * (m_now_graph - 1)) {

		m_next_graph = m_now_graph - 1;
	}

	// ラインより上の場合
	if ((-m_pos.y + GRAPH_SCALE_H - SCREEN_DIFFERENCE) + BG_MOVE_LINE
		>= (-GRAPH_SCALE_H) * (m_next_graph - 1)) {

		m_now_graph = m_next_graph - 1;
	}

	// デバッグエリア
	{

		if (m_pback_str[m_now_graph % 4] == ERROR || m_pback_str[m_next_graph % 4] == ERROR) {
			m_now_graph *= -1;
			m_next_graph *= -1;
		}

		// 最後の画像なら下まで行かせないようにする
		if (m_now_graph == 0 && -m_pos.y >= 0) {
			// 参照でないといけないかも
			m_move_pos.x = 0;
			m_move_pos.y = 0;

			m_now_graph = 0;
			m_next_graph = 1;
		}
	}
}

void BackGround::Update() {

	PosUpdate();
	Scroll();
}

void BackGround::Draw() {

	// 1枚目描画
	Texture::Draw2D(m_pback_str[m_now_graph % 4], 0.f, m_pos.y - (float)SCREEN_DIFFERENCE + (-GRAPH_SCALE_H * m_now_graph));
	// 2枚目描画
	Texture::Draw2D(m_pback_str[m_next_graph % 4], 0.f, m_pos.y - (float)SCREEN_DIFFERENCE + (-GRAPH_SCALE_H * m_next_graph));


	Texture::Draw2D("player1.png", -m_pos.x, ((-m_pos.y) + (GRAPH_SCALE_H - SCREEN_DIFFERENCE) + 10.f));

	Texture::Draw2D("renga.png", m_pos.x, -m_pos.y + (-GRAPH_SCALE_H) * m_now_graph);

	int debug1 = (-GRAPH_SCALE_H * m_now_graph);

	//OX::DebugFont::print(100, 100, 1000, "-back_pos => %f", -back_pos_up.y);
	//OX::DebugFont::print(100, 200, 500, "back_pos => %f", back_pos_up.y);
	////OX::DebugFont::print(100, 300, 0, "condition:%d",debug1);
	//OX::DebugFont::print(100, 600, 100, "now_graph => %d", now_graph);
	//OX::DebugFont::print(100, 700, 100, "next_graph => %d", next_graph);
	//
	//OX::DebugFont::draw(dev);
	//OX::DebugFont::clear();
}

