#include"UV.h"
#include<vector>



// コンストラクタ
UV::UV(int div_w,int div_h) {

	width_div_num = div_w;
	height_div_num = div_h;
	total_div_num = width_div_num * height_div_num;

	// テクスチャ座標の初期化(頂点は全体に設定)
	uv_up_left_pos.x = 0.f;
	uv_up_left_pos.y = 0.f;
	uv_up_right_pos.x = MAX_UV_SIZE;
	uv_up_right_pos.y = 0.f;
	uv_down_left_pos.x = 0.f;
	uv_down_left_pos.y = MAX_UV_SIZE;
	uv_down_right_pos.x = MAX_UV_SIZE;
	uv_down_right_pos.y = MAX_UV_SIZE;
}


void UV::AnimationToTheRightDivGraph(int div_num) {

	// 画像サイズを超えたら最大値を入れる
	div_num = total_div_num < div_num ? total_div_num : div_num;
	div_num = 0 > div_num ? total_div_num : div_num;

	// 先の頂点を含む
	const float NEXT_GO_GRAPH = 1.f;

	// 切り取る幅を変数に代入
	int div_x = 0;
	int div_y = 0;

	// 最初の0だけはあまり算出来ないので応急措置
	if (div_num == 0) {
		div_x = div_num;
		div_y = div_num;
	}
	else {
		// y座標は変換しないと正しい値が取れない
		div_x = ((div_num) % width_div_num);
		div_y = ((div_num) / width_div_num);// 割った数分,y座標が進む
	}
	// 切り出すテクスチャ座標を(最大サイズ/横の分割数=一つの画像の大きさ)*全体の位置で割り出す
	// 小さな画像を掛け算でずらしていく
	
	// 左上
	uv_up_left_pos.x =    (MAX_UV_SIZE / width_div_num) * div_x;
	uv_up_left_pos.y =    (MAX_UV_SIZE / height_div_num)* div_y;
	// 右上
	uv_up_right_pos.x =   (MAX_UV_SIZE / width_div_num) * (div_x + NEXT_GO_GRAPH);
	uv_up_right_pos.y =   (MAX_UV_SIZE / height_div_num)* div_y;
	// 左下
	uv_down_left_pos.x =  (MAX_UV_SIZE / width_div_num) * div_x;
	uv_down_left_pos.y =  (MAX_UV_SIZE / height_div_num)* (div_y + NEXT_GO_GRAPH);
	// 右下
	uv_down_right_pos.x = (MAX_UV_SIZE / width_div_num) * (div_x + NEXT_GO_GRAPH);
	uv_down_right_pos.y = (MAX_UV_SIZE / height_div_num)* (div_y + NEXT_GO_GRAPH);
}


void UV::AnimationToTheLeftDivGraph(int div_num) {

	// 画像サイズを超えたら最大値を入れる
	div_num = total_div_num < div_num ? total_div_num : div_num;
	div_num = 0 > div_num ? total_div_num : div_num;

	// 先の頂点を含む
	const float NEXT_GRAPH = 1.f;

	// 切り取る幅を変数に代入
	int div_x = 0;
	int div_y = 0;

	// 最初の0だけはあまり算出来ないので応急措置
	if (div_num == 0) {
		div_x = div_num;
		div_y = div_num;
	}
	else {
		// y座標は変換しないと正しい値が取れない
		div_x = ((div_num) % width_div_num);
		div_y = ((div_num) / width_div_num);// 割った数分,y座標が進む
	}
	// 切り出すテクスチャ座標を(最大サイズ/横の分割数=一つの画像の大きさ)*全体の位置で割り出す
	// 小さな画像を掛け算でずらしていく

	// 最大サイズを引く

	// 左上
	uv_up_left_pos.x =  (MAX_UV_SIZE - (MAX_UV_SIZE / width_div_num)) - (MAX_UV_SIZE / width_div_num) * div_x;
	uv_up_left_pos.y = (MAX_UV_SIZE / height_div_num)* div_y;
	// 右上
	uv_up_right_pos.x = MAX_UV_SIZE - (MAX_UV_SIZE / width_div_num) * div_x;
	uv_up_right_pos.y = (MAX_UV_SIZE / height_div_num)* div_y;
	// 左下
	uv_down_left_pos.x = (MAX_UV_SIZE - (MAX_UV_SIZE / width_div_num)) - (MAX_UV_SIZE / width_div_num) * div_x;
	uv_down_left_pos.y = (MAX_UV_SIZE / height_div_num)* (div_y + NEXT_GRAPH);
	// 右下
	uv_down_right_pos.x = MAX_UV_SIZE - (MAX_UV_SIZE / width_div_num) * div_x;
	uv_down_right_pos.y = (MAX_UV_SIZE / height_div_num)* (div_y + NEXT_GRAPH);
}


// 拡縮させながらテクスチャ座標指定する
//void UV::UVGauge(const float &scale_x, const float &scale_y, const float&whole_scale_x, const float&whole_scale_y) {
//
//	float uv_cut_x = whole_scale_x/scale_x;
//	float uv_cut_y = whole_scale_y/scale_y;
//
//}


// 特定の位置の分割画像を取り出す
//void UV::UAxisVAxisSelectionDivGraph(int u, int v) {
//
//}



// アノテーションコメント
// todo
// fixme
// hack
// 

/*
std::vector<D3DXVECTOR2>uv_buf_vec{ uv_left_up_buffer, uv_right_up_buffer,
uv_left_down_buffer,uv_right_down_buffer };

uv_buf_vec[0].x = (WHOLE_UV_BUFFER / width_div_num) * div_num;
uv_buf_vec[0].y = (WHOLE_UV_BUFFER / height_div_num) * div_num;
*/

/*

// 1/4=0.25*0=0  1/4=0.25*1=0.25 1/4=0.25*2=0.5
// vectorで回せそう
// yだけ前進させればいい,だがxも0に戻さないと画像の規定値をこえてしまう

// 全体-横の切り出す値
// 反対の位置を出す為の全体 - 余り算で後ろの残りの画像 = 取り出したい画像
// 最後に分割位置-1はuv座標は0から始まる為一つずらす

// 8   %    11=3
// 8   %    10=2
// 8   %    9=1
// 8   %    8=0
// 8   %	7=7
// 8   %	6=6
// 8   %	5=5
// 8   %	4=4
*/