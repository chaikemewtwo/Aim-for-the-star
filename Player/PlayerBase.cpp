#include "PlayerBase.h"


PlayerBase::PlayerBase() {
	
}

void PlayerBase::Update() {
	// HACK:自機2の操作を分離する
	Keybord& kb = Keybord::getInterface();

	// 泳ぎインターバルカウントアップ
	++swim_interval_count;

	// 泳ぎアニメーション
	swim_animetion_num = swim_interval_count / 6;

	// 泳ぐ（ジャンプ）
	if (kb.press('V') && swim_interval_count >= (int)SWIM_INTERVAL) {
		SwimUp();
		swim_interval_count = 0;
	}
	else {
		// 重力負荷
		AddGravity();
	}

	// 左右角度変更
	// 左
	if ((kb.on('A'))) {
		AngleAdjust(false);
	}
	// 右
	if ((kb.on('D'))) {
		AngleAdjust(true);
	}
}

void PlayerBase::Draw() {
	// 自機1のものを使用
	Texture::Draw2D("Resource/de_swim.png",
		pos_x,
		pos_y,
		TEXTURE_SIZE_X,
		TEXTURE_SIZE_Y,
		star_angle,
		0.5f,
		0.5f,
		true,
		4,
		4,
		swim_animetion_num
	);
}

void PlayerBase::AddGravity() {
	// 下方向へ移動
	drop_speed += GRAVITY;
	pos_y += drop_speed;
}

void PlayerBase::SwimUp() {
	// 上方向へ移動
	drop_speed = Y_ADD;
	pos_y += drop_speed;
}

void PlayerBase::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (star_angle < MAX_ANGLE && star_angle > -MAX_ANGLE) {
		star_angle += is_move_right ? X_ADD : -X_ADD;
	}
	else if (star_angle > -MAX_ANGLE) {
		star_angle = MAX_ANGLE - 1.f;
	}
	else if (star_angle < MAX_ANGLE) {
		star_angle = -MAX_ANGLE + 1.f;
	}
}
