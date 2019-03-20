#include "../Star1/Star1.h"

Star1::Star1() {
	// 位置初期化
	pos_x = (float)WINDOW_W / 2.f - 100.f;
	pos_y = (float)WINDOW_H / 2.f;
	speed = 0.f;
	interval_count = SWIM_INTERVAL;
}

Star1::~Star1() {

}

void Star1::Update() {
	Keybord& kb = Keybord::getInterface();

	++interval_count;

	// 泳ぐ（ジャンプ）
	if (kb.press('V') && interval_count >= SWIM_INTERVAL) {
		SwimUp();
		interval_count = 0;
	}
	else {
		// 重力負荷
		AddGravity();
	}

	// 左右移動
	// 左
	if ((kb.on('A'))) {
		XMove(false);
	}
	// 右
	if ((kb.on('D'))) {
		XMove(true);
	}
}

void Star1::Draw() {
	Texture::Draw2D("Resource/starfish_sample1.png",
		pos_x,
		pos_y,
		TEXTURE_SIZE_X, 
		TEXTURE_SIZE_Y, 
		0.5f, 
		0.5f);
	// HACK:第六引数で角度変更
}
