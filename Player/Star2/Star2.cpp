#include "../Star2/Star2.h"

Star2::Star2() {
	// 初期化
	// 位置
	pos_x = (float)WINDOW_W / 2.f + 100.f;
	pos_y = (float)WINDOW_H / 2.f;

	// 落下速度
	drop_speed = 0.f;

	// 傾き
	star_angle = 0.f;

	// 泳ぎコマンドインターバル
	swim_interval_count = SWIM_INTERVAL;

	// 泳ぎアニメーション番号
	swim_animetion_num = 0;
}

Star2::~Star2() {

}
