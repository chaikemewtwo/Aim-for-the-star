#pragma once
#include"../Window/Window.h"

// 引数は4~5が目安

namespace Texture {

	void Draw2D(const char*file_name, float x, float y, float scale_w = 1.f, float scale_h = 1.f, float angle = 0.f, float cx = 0.0f, float cy = 0.0f,bool uv_cut=false,int ux=0.f,int uy=0.f,int graph_num=0);

	// 描画関係
	void Draw2DGraph(const char*file_name, const float&pos_x, const float&pos_y);
	void Draw2DTransGraph(const char*file_name, const float&pos_x, const float&pos_y, const float &scale_x=0.f, const float&scale_y=0.f, const float&angle=0.f);
	void Draw2DRotaGraph(const char*file_name, const float&pos_x, const float &pos_y, const float&angle=0.f);
	void Draw2DAnimationGraph(const char*file_name, const float&pos_x, const float&pos_y, const int&u_cut_num=0.f, const int&v_cut_num=0.f, const int&anim_num=0.f);
	void Draw2DPixelSizeGraph(const char*file_name, const float&pos_x, const float&pos_y, const float pixel_size=64.f);
}