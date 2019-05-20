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
	TEXTURE_DATA() {
		Texture = nullptr;
		Width = 0.f;
		Height = 0.f;
	}

	LPDIRECT3DTEXTURE9 Texture;
	float Width;
	float Height;

	operator LPDIRECT3DTEXTURE9() const {
		return Texture;
	}

	LPDIRECT3DTEXTURE9 GetTexture()const {
		return Texture;
	}
};

// テクスチャを保存するテクスチャリスト
extern std::unordered_map < std::string, TEXTURE_DATA > tex_list;


namespace Texture {

	// テクスチャのロード
	void Load(const char*file_name);
	// Exの方のロード
	void LoadEx(const char * file_name,UINT width = 0.f,UINT height = 0.f, DWORD color_key = NULL);
	// 解放
	void Release();
}