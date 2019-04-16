#pragma once

// 自作
#include"../Window/Window.h"

// 既存
#include<d3dx9.h>
#include<unordered_map>

#pragma comment(lib,"d3dx9.lib")


// テクスチャデータを格納する。
struct TEXTURE_DATA
{
	LPDIRECT3DTEXTURE9 Texture = nullptr;
	float Width = 0;
	float Height = 0;

	operator LPDIRECT3DTEXTURE9() const {
		return Texture;
	}
};

// テクスチャを保存するテクスチャリスト
extern std::unordered_map < std::string, TEXTURE_DATA > tex_list;


namespace Texture {

	// テクスチャのロード
	void Load(const char*file_name);

	// 解放
	void Release();
}