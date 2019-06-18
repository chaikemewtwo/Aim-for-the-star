#pragma once
#include"../D3D9/D3D9.h"

// 何をすれば何をできるかを書く

/* UVクラス使い方講座

 この関数は統合画像専用です

 Draw系と併用して使用します

 RightRotationDivGraph(int divsion_num)
 ...統合画像を右から切り取っていく関数

 div_w...      統合画像の横の分割数
 div_h...      統合画像の縦の分割数
 divsion_num...分割後の全ての画像

 使用例

 ①コンストラクタで統合画像を縦4横4で切り取り
 UV(4,4);


 ②(3,0)番目の画像を切り取る
 RightAdvanceDivGraph(3);


 ③切り取った統合画像をゲッターで受け取る

 D3DXVECTOR2 * = & D3DXVECTOR2 GetUvUpLeftBuffer()

 ④最後にそれぞれの頂点に振り分ける

 // VERTEX3Dの初期化
 CUSTOM_VERTEX cv[] = 
 {
 { x1,y1,0.0f,1.0f, up_left->x,up_left->y },       // 左上
 { x2,y1,0.0f,1.0f ,up_right->x,up_right->y },     // 右上
 { x2,y2,0.0f,1.0f ,down_right->x,down_right->y }, // 右下
 { x1,y2,0.0f,1.0f ,down_left->x,down_left->y },   // 左下
 };

*/

class UV {
public:

	// 引数に横と縦の分割したい画像数を入れる
	UV(int div_w, int div_h);

	// 右から画像を分割する
	void AnimationToTheRightDivGraph(int divsion_num);
	// 左から画像を分割する
	void AnimationToTheLeftDivGraph(int divsion_num);

	// HACK　まだ完成していません
	//void UAxisVAxisSelectionDivGraph(int u, int v);

	// 拡縮させながらテクスチャ座標指定する
	/*
	scale_xは実際に拡縮させる大きさ
	while_scaleは全体の大きさ
	*/
	//void UVGauge(const float &scale_x, const float &scale_y,const float&whole_scale_x,const float&whole_scale_y);

	// 左上頂点
	D3DXVECTOR2 GetUvUpLeftPos(){
		return uv_up_left_pos;
	}
	// 右上頂点
	D3DXVECTOR2 GetUvUpRightPos() {
		return uv_up_right_pos;
	}
	// 左下頂点
	D3DXVECTOR2 GetUvDownLeftPos() {
		return uv_down_left_pos;
	}
	// 右下頂点
	D3DXVECTOR2 GetUvDownRightPos() {
		return uv_down_right_pos;
	}
private:

	// 最大の頂点バッファ
	const float MAX_UV_SIZE = 1.f;

private:

	// 分割する合計の数
	int total_div_num;

	// 縦に分割する数
	int height_div_num;

	// 横に分割する数
	int width_div_num;

	// テクスチャ頂点座標
	D3DXVECTOR2 uv_up_left_pos;
	D3DXVECTOR2 uv_up_right_pos;
	D3DXVECTOR2 uv_down_left_pos;
	D3DXVECTOR2 uv_down_right_pos;
};

/*

仕様は

ListDivGraph(1)としたら
左から1番目の画像が読み込まれる

多少大まかになるが汎用的なUVクラスをつくるか
List,Fan,Stripなどに独自で対応したものをそれぞれに作るか(その場合分割過程のみ同じになるが
それ以外は派生したものになる)

統合画像は2乗で割れる

2乗ずつでないと正確な分割ができないが、一応奇数も作って置く
2,4,8,16
*/