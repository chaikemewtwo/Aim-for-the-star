#include"../Texture/Texture.h"
#include"../D3D/D3D9.h"



std::unordered_map < std::string, TEXTURE_DATA >tex_list;


namespace Texture {

	// scale_x scale_y
	void Load(const char*file_name)// int型にしてDrawGraphにしてもいいかも。その場合はvector型を使う。
	{
		D3DXIMAGE_INFO info;

		if (FAILED(D3DXGetImageInfoFromFile(file_name, &info))) {
			MessageBoxA(0, "ファイル読み込みエラー", NULL, MB_OK);
			return;
		}

		D3DXCreateTextureFromFile(dev, file_name, &tex_list[file_name].Texture);

		// 最初はサイズ指定をしなければいけない。
		tex_list[file_name].Width = (float)info.Width;
		tex_list[file_name].Height = (float)info.Height;
	}

	// 2の累乗でテクスチャサイズが指定できる

	// HACK
	void LoadEx(const char *file_name,UINT width,UINT height,DWORD color_key,float u,float v)
	{
		D3DXIMAGE_INFO info;

		if (FAILED(D3DXGetImageInfoFromFile(file_name, &info))) {
			MessageBoxA(0, "ファイル読み込みエラー", NULL, MB_OK);
			return;
		}

		// 最初はサイズ指定をしなければいけない。
		tex_list[file_name].Width = (float)info.Width;
		tex_list[file_name].Height = (float)info.Height;
		tex_list[file_name].Uv.x = u;
		tex_list[file_name].Uv.y = v;

		// EXバージョンの読み込み
		D3DXCreateTextureFromFileEx(
			dev,                     // window_device
			file_name,               // ファイル名
			info.Width + width,                   // 読み込むファイル幅
			info.Height + height,                  // 読み込むファイル縦幅
			1,                    // ミップマップレベル
			0,        // テクスチャの使い方
			D3DFMT_UNKNOWN,          // カラーフォーマット
			D3DPOOL_MANAGED,         // テクスチャのメモリ管理方法
			D3DX_DEFAULT,                    // フィルタリング方法
			D3DX_DEFAULT,                    // ミップマップのフィルタリング方法
			NULL,// 0x0000ff00 
			NULL,
			NULL,
			&tex_list[file_name].Texture);
	}

	void Release() {

		for (const auto& it : tex_list) {
			if (it.second.Texture != nullptr) {
				it.second.Texture->Release();
			}
		}

	}

}

// テスト用のコード
/*
#include"Texture.h"
#include"Window.h"
// 実体確保
TEXTURE_DATA g_Texture;


bool MakeFile(char *file_name)
{
	// テクスチャ読み込み
	// D3DXCreateTextureFromFileAならいけた。
	if (FAILED(D3DXCreateTextureFromFileA(dev,
		                                 file_name,
		                                 &g_Texture.m_pTexture)))
	{
		return false;
	}
	else {
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if (FAILED(g_Texture.m_pTexture->GetLevelDesc(0, &desc)))
		{
			g_Texture.m_pTexture->Release();
			g_Texture.m_pTexture = NULL;
			return false;
		}

		g_Texture.Width = (float)desc.Width;
		g_Texture.Height = (float)desc.Height;

	}

	return true;
}




void Costum_VertexCreate() {



	// VERTEX3Dの初期化
	VERTEX3D bg[] =
	{

		// 画像全体を設定
		// 左上頂点
		{ 0.0f,0.0f,0.0f,1.0f, 0.0f,0.0f },
		// 右上頂点
	{ g_Texture.Width,0.f,0.0f,1.0f ,1.0f,0.0f },
	// 右下頂点
	{ g_Texture.Width,g_Texture.Height,0.0f,1.0f ,1.0f,1.0f },
	// 左下頂点
	{ 0.0f,g_Texture.Height,0.0f,1.0f ,0.0f,1.0f },


	};


	// CustomVertexの指定
	// DirectXに通知
	dev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	// テクスチャの指定
	dev->SetTexture(0, g_Texture.m_pTexture);

	// ポリゴンの描画
	dev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,
		2,
		bg,
		sizeof(VERTEX3D));

	DrawEnd();

}

// テクスチャのリリース
void Release() {


	// テクスチャの解放
	if (g_Texture.m_pTexture != NULL)
	{
		g_Texture.m_pTexture->Release();
		g_Texture.m_pTexture = NULL;
	}
}
*/





