#pragma once
#include"../D3D9/D3D9.h"
#include"../Window/Window.h"


namespace Texture {


	enum SamplerStateType {
		CLAMP,              // つなぎ目なし
		MIRROR,				// 反転
	};


	// 描画関係
	void Draw2DGraph(
		const char*file_name,
		const float&pos_x,
		const float&pos_y
	);


	void Draw2DTransGraph(
		const char*file_name,
		const float&pos_x,
		const float&pos_y,
		const float&scale_x,
		const float&scale_y,
		const float&angle
	);


	void Draw2DRotaGraph(
		const char*file_name,
		const float&pos_x,
		const float&pos_y,
		const float&angle
	);


	void Draw2DAnimationGraph(
		const char*file_name,
		const float&pos_x,
		const float&pos_y,
		const int&tu_cut_num,
		const int&tv_cut_num,
		const int&animation_num
	);


	// UVをずらす関数
	void Draw2DUVShift(
		const char*file_name,
		const float &pos_x,
		const float &pos_y,
		const float&shift_tu,
		const float&shift_tv
	);


	void Draw2DAnimationUVSampler(
		const char * file_name,
		const float&pos_x,
		const float&pos_y,
		const int&tu_cut_num,
		const int&tv_cut_num,
		const int&animation_num,
		SamplerStateType sampler_state_type
	);


	// サイズ系の関数が多くなってきたのでnamespaceでまとめる
	namespace Size {

		// 画像サイズを取得する関数
		float GetGraphSizeX(const char*file_name);
		float GetGraphSizeY(const char*file_name);
		D3DXVECTOR2 GetGraphSizeVec2(const char*file_name);

		// 統合画像のサイズを取得する関数
		float GetDivGraphSizeXByCutSize(const char*file_name, int div_num_x);
		float GetDivGraphSizeYByCutSize(const char*file_name, int div_num_y);
		D3DXVECTOR2 GetGraphSizeVec2ByCutSize(const char*file_name, int div_num_x, int div_num_y);
	}


	// Draw2Dの使い方

	/*
	引数1 ファイル名
	引数2,3 位置
	引数4,5 大きさ
	引数6 角度
	引数7,8 オフセット位置x,y(どこから描画を始めるか)
	引数9 分割総数
	引数10 分割する数、横
	引数11 分割する数、縦
	引数12 分割した現在の画像(アニメーションをするならここを動かす)
	*/

	/*
	アニメーションするならまず分割画像を分割する

	例
	16枚の統合画像を分割するとする
	横4縦2で分割するとする

	引数9で16の整数を入れる
	引数10で4を入れる
	引数11で2を入れる
	引数12は整数型で現在の画像を指定する

	引数12(graph_num)の仕組み(アニメーションする場合は通常見なくて大丈夫です)
	横に走査して描画していく。
	横の最大数まで来たら一段下に下がる。
	*/

	void Draw2D(
		const char*file_name,
		float x,
		float y,
		float scale_w = 1.f,
		float scale_h = 1.f,
		float angle = 0.f,
		float cx = 0.0f,
		float cy = 0.0f,
		bool uv_cut = false,
		int ux = 0.f,
		int uy = 0.f,
		int graph_num = 0,
		float u = 0.f,
		float v = 0.f,
		SamplerStateType type = CLAMP,
		DWORD alpha_color = 255
	);

}
