#pragma once
#include"../Window/Window.h"



/*  3Dテクスチャボード

マトリックス計算は気にしなくていい。
D3DXMATRIX

①Transformに先に数値をいれ、
②Make3DMatrixでマトリックス計算を任せる。
③戻り値でマトリックスを受け取る。
④Draw3DListで描画マトリックスを入れる。

*/

// MEMO 値を渡したい場合はconst&で値を変更したいならポインタ渡し,値渡しは原則禁止
// MEMO 引数が多い場合は処理ごとに関数分けできていない可能性がある

namespace Texture {

	enum Dir {
		NORTH,
		SOUTH,
		EAST,
		WEST,
		FLOOR,
	};

	// マトリックスで使う構造体
	struct Transform {

		// D3DXVECTOR3 move, angle, scale;

		float move_x, move_y, move_z;
		float angle_x, angle_y, angle_z;
		float scale_x, scale_y, scale_z;

		Transform();
		Transform(float move_x, float move_y, float move_z,
			float angle_x, float angle_y, float angle_z,
			float scale_x, float scale_y, float scale_z);
	};

	Texture::Transform DirRotationTransform(Dir dir,Texture::Transform& ts);
	D3DXMATRIX Make3DMatrix(Texture::Transform &ts);
	void Draw3D(const char*file_name, const D3DXMATRIX &mat_world,const float &cx,const float &cy,const bool &cull_none=true,bool uv_cut = false, int u_axis = 0, int v_axis = 0, int graph_num = 0);
}

// 回転が変わっている