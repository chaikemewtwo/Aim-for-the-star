#include "PlayerBase.h"
#include <math.h>


PlayerBase::PlayerBase() {
	// 落下速度
	drop_speed = 0.f;

	// 傾き
	star_angle.x = 0.f;
	star_angle.y = 0.f;

	star_add.x = X_ADD;
	star_add.y = Y_ADD;

	// 泳ぎコマンドインターバル
	swim_interval_count = SWIM_INTERVAL;

	// 泳ぎアニメーション番号
	swim_animetion_num = 0;
}

Vector2D PlayerBase::tagGetStarVector(Vector2D v) {
	// ベクトルの長さ
	float length = pow((v.x * v.x) + (v.y * v.y), 0.5);

	pos.x = v.x / length;
	pos.y = v.y / length;

	return pos;
}

void PlayerBase::Update() {
	// HACK:自機2の操作を分離する
	Keybord& kb = Keybord::getInterface();

	// 泳ぎインターバルカウントアップ
	++swim_interval_count;

	// 泳ぎアニメーション
	swim_animetion_num = swim_interval_count / SWIM_ANIMATION_SUPPORT_NUMBER;

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
	// 第7、8引数が0.5fずつで中心座標から描画
	Texture::Draw2D(
		"Resource/de_swim.png",
		pos.x,
		pos.y,
		TEXTURE_SIZE_X,
		TEXTURE_SIZE_Y,
		star_angle.x,
		0.5f,
		0.5f,
		true,
		TEXTURE_PARTITION_X_NUMBER,
		TEXTURE_PARTITION_Y_NUMBER,
		swim_animetion_num
	);
}

void PlayerBase::AddGravity() {
	// 下方向へ移動
	drop_speed += GRAVITY;
	pos.y += drop_speed;
}

void PlayerBase::SwimUp() {
	// ベクトル付与
	pos = tagGetStarVector(star_add);
	// HACK:位置を初期化してしまっている
}

void PlayerBase::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (star_angle.x < MAX_ANGLE && star_angle.x > -MAX_ANGLE) {
		star_angle.x += is_move_right ? X_ADD : -X_ADD;
	}
	// 角度変更範囲設定
	else if (star_angle.x > -MAX_ANGLE) {
		star_angle.x = MAX_ANGLE - 1.f;
	}
	else if (star_angle.x < MAX_ANGLE) {
		star_angle.x = -MAX_ANGLE + 1.f;
	}
}
