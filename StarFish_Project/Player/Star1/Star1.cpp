﻿#include "../Star1/Star1.h"


Star1::Star1() {
	// 初期化
	// 位置（画面左）
	m_pos.x = (float)WINDOW_W / 2.f - 200.f;
	m_pos.y = (float)WINDOW_H / 2.f;

	// 画像
	m_player_texture = "Resource/de_swim.png";
	//m_player_texture[WAIT] = "Resource/de_wait.png";
	/*m_player_texture[SWIM] = "Resource/de_swim.png";*/
}
