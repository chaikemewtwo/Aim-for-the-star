#include"Player.h"
//#include"../ObjectVisitor.h"
#include"../Map/BackGround.h"



// コンストラクタ
Player::Player() {

	m_pos.x = m_pos.y = 0.f;
	m_move_pos.x = m_move_pos.y = SPEED;

	m_pos.x = (BackGround::GRAPH_SCALE_W / 2) - 100;
	m_pos.y = (-BackGround::GRAPH_SCALE_H / 2) + 100;
}


// 自機操作
void Player::Control() {

	Keybord&kb = Keybord::getInterface();

	// 移動ベクトルを無しにする
	m_move_pos.x = m_move_pos.y = 0;

	// 自機の操作
	{
		if (kb.on(VK_LEFT)) {
			m_move_pos.x-=SPEED;
		}
		if (kb.on(VK_RIGHT)) {
			m_move_pos.x += SPEED;
		}
		if (kb.on(VK_UP)) {
			m_move_pos.y += SPEED;
		}
		if (kb.on(VK_DOWN)) {
			m_move_pos.y -= SPEED;
		}

		// 加算
		m_pos += m_move_pos;

		kb.update();
	}
}

void Player::Draw() {


	// 自機(y座標は動かさず、背景を動かして、動かしているように見せかける)
	Texture::Draw2D("Texture/de_swim.png", m_pos.x,(BackGround::GRAPH_SCALE_H / 2), -384.f, -384.f);


	//OX::DebugFont::print(100, 100, 1000, "m_player_pos.x => %f", m_pos.x);
	//OX::DebugFont::draw(dev);
	//OX::DebugFont::clear();
}

// 訪問を受け入れるメソッド
//void Player::AcceptVisitor(ObjectVisitor*visit) {

	//visit->VisitPlayer(this);
//}
