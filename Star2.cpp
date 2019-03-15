#include "Star2.h"

Star2::Star2() {
	// 位置初期化
	pos_x = (float)WINDOW_W / 2.f + 100.f;
	pos_y = (float)WINDOW_H / 2.f;
	speed = 0.f;
	interval_count = SWIM_INTERVAL;
}

Star2::~Star2() {

}


void Star2::Update() {
	Keybord& kb = Keybord::getInterface();

	++interval_count;
	
	// 泳ぐ（ジャンプ）
	if (kb.press('N')&& interval_count >= SWIM_INTERVAL) {
		SwimUp();
		interval_count = 0;
	}
	else {
		// 重力負荷
		AddGravity();
	}

	// 左右移動
	// 左
	if (kb.on(VK_LEFT)) {
		XMove(false);
	}
	// 右
	if (kb.on(VK_RIGHT)) {
		XMove(true);
	}
}

void Star2::Draw() {
	Texture::Draw2D("Texture/starfish_sample2.png", pos_x, pos_y, TEXTURE_SIZE_X, TEXTURE_SIZE_Y, 0.f, 0.5f, 0.5f);
	// HACK:第六引数で角度変更
}
