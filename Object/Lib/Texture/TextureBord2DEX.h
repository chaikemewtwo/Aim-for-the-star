#pragma once
#include"D3D9.h"
#include<string>



/*

TextureBord2Dの拡張機能

引数が長かったのでそれぞれ
分けて設定できる。

Clear関数を使えばこのクラスを使いまわせる

デメリットは使わない変数まで生成してしまう可能性がある。
*/

/* 使い方例

Texture::SetDraw2DTemplate("tep.png",100.f,100.f);
Texture::Draw2DGraphEX();

*/

namespace Texture {

	// 画像名関係

	void SetFileNameEX(const char*file_name);
	void SetFileNameEX(std::string &file_name);

	// 移動回転拡縮関係
	void SetPostionEX(const float&pos_x, const float&pos_y);
	void SetScaleEX(const float&scale_x, const float&scale_y);
	void SetAngleEX(const float&angle);
	void SetTransformEX(const float&pos_x, const float&pos_y, const float&scale_x, const float&scale_y, const float&angle);

	// 位置変更
	void SetOfset(const float&cx, const float&cy);

	// UV関係
	void SetUV(const int&u_cut_num, const int&v_cut_num, const bool&is_uv);
	void SetAnimation(const int&animation_num);

	// 描画のセットテンプレート
	void SetDraw2DTemplate1(const char*file_name, const float&pos_x, const float&pos_y);
	void SetDraw2DTemplate2(const float&scale_x, const float scale_y, const float angle);
	void SetDraw2DTemplate3();

	// 最後に初期化せずに描画する
	void Draw2DGraphEXAfterNoInit();// こっちの方が速い、でも内部の値は初期化されていない

	// 描画した最後に初期化する
	void Draw2DGraphEX();// こっちは上より遅いけど、初期化するので、安定している

	// 初期化関数
	void Clear();
}






/*
class TextureBord2DEX
{
public:

	// 各種アクセサ
	void SetNormalConfig(const char*file_name, const float&pos_x, const float &pos_y);

	void SetTransform(const D3DXVECTOR2&pos, const D3DXVECTOR2&scale, const float&angle);
	void SetTransform
	   (const float & pos_x,   const float & pos_y,
		const float & scale_x, const float & scale_y,
		const float & angle);
	
	void SetFileName(const char*file_name);
	void SetFileName(const std::string &file_name);

	void SetPostion(const D3DXVECTOR2&pos);
	void SetPostion(const float&pos_x, const float&pos_y);

	void SetScale(const D3DXVECTOR2&scale);
	void SetScale(const float&scale_x, const float&scale_y);

	void SetAngle(const float &angle);

	void SetOfSetPos(const D3DXVECTOR2&ofset);

	// string変換拡張関数
	void operator =(const std::string & file_name) {
		// c_strでstring型からconst char*型に変換
		m_file_name = file_name.c_str();
	}

	// 全ての値を一旦デフォルト値に戻す
	void Clear() {}

	// 設定した値で描画する
	void GoDraw() {
		Texture::Draw2D(m_file_name, m_pos.x, m_pos.y, m_scale.x, m_scale.y, m_angle,
			m_ofset.x, m_ofset.
			y, m_uv_cut, m_u_x, m_u_y, m_animation_num);
	}
		 

private:
	const char*m_file_name;   // ファイル名
	D3DXVECTOR2 m_pos;		  // 位置
	D3DXVECTOR2 m_scale;	  // 拡縮
	float m_angle;			  // 回転
	D3DXVECTOR2 m_ofset;	  // センター位置(どこから描画するか)
	bool m_uv_cut;			  // UVカットするか(する=TRUE)
	int m_u_x;				  // 横のUVで切り取る数
	int m_u_y;				  // 縦のUVで切り取る数
	int m_animation_num;	  // アニメーションナンバー
};
*/

/*

animation_numは
UV分割総数を順番に入れていくと
全てのアニメーションを
行える。
しかし、アニメーションを行う範囲は
2の累乗の空白部分も描画してしまうので、
それは独自で制限する必要がある

*/