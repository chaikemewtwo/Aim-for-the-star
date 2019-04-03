#include "PlayerBase.h"
#include <cmath>


PlayerBase::PlayerBase() {
	// 移動速度
	move_speed = 2.f;

	// 落下速度
	drop_speed = 0.f;

	// 傾き
	character_angle = 0.f;

	// 泳ぎコマンドインターバル
	swim_interval_count = SWIM_INTERVAL;

	// アニメーション番号
	animation_num = 0;
}

void PlayerBase::Update() {
	// HACK:自機2の操作を分離する
	Keybord& kb = Keybord::getInterface();

	// 泳ぎアニメーション
	// HACK:Stateパターン内で管理する
	animation_num = swim_interval_count / SWIM_ANIMATION_SUPPORT_NUMBER;

	//重力を付与(常時)
	AddGravity();

	// 左右角度変更
	// 左
	if ((kb.on('A'))) {
		AngleAdjust(false);
	}
	// 右
	if ((kb.on('D'))) {
		AngleAdjust(true);
	}
	// キャラクターが向いている角度に向かって泳ぐ
	if (swim_interval_count >= SWIM_INTERVAL) {
		if (kb.press('V')) {
			swim_interval_count = 0;
		}
	}
	else {
		SwimUp();
		// 泳ぎインターバルカウントアップ
		++swim_interval_count;
	}
}

void PlayerBase::Draw() {
	// 自機2にも自機1のものを使用中
	// 第7、8引数が0.5fずつで中心座標から描画
	Texture::Draw2D(
		"Resource/de_swim.png",
		pos_x,
		pos_y,
		TEXTURE_SIZE_X,
		TEXTURE_SIZE_Y,
		character_angle,
		0.5f,
		0.5f,
		true,
		TEXTURE_PARTITION_X_NUMBER,
		TEXTURE_PARTITION_Y_NUMBER,
		animation_num
	);
}

void PlayerBase::AddGravity() {
	// 常時下方向へ負荷がかかる
	pos_y += GRAVITY;
}

void PlayerBase::AngleAdjust(bool is_move_right) {
	// 自機傾き変更、TRUEで右へ傾く
	if (character_angle < MAX_ANGLE && character_angle > -MAX_ANGLE) {
		character_angle += is_move_right ? ANGLE_ADD : -ANGLE_ADD;
	}
	// 角度変更範囲設定
	else if (character_angle > -MAX_ANGLE) {
		character_angle = MAX_ANGLE - 1.f;
	}
	else if (character_angle < MAX_ANGLE) {
		character_angle = -MAX_ANGLE + 1.f;
	}
}

void PlayerBase::SwimUp() {
	// ベクトルの長さ(上方向への移動)
	move_x = sin(character_angle * PI / (float)180.f) * move_speed;
	move_y = cos(character_angle * PI / (float)180.f) * move_speed;

	// 移動量インクリメント
	pos_x += move_x;
	pos_y -= move_y;
}