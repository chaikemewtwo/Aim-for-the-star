#pragma once
#include"../Window/Window.h"


/* DirectXの描画 */

namespace Graphics {


	// D3Dの初期化、ウィンドウモード
	LPDIRECT3DDEVICE9 InitD3D(HWND hWnd);
	// D3Dの初期化、フルスクリーンモード
	LPDIRECT3DDEVICE9 InitD3DFullScreenMode(HWND h_wnd);

	// 描画開始
	bool DrawStart();
	// 描画終了
	void DrawEnd(); 

	// バックバッファ(解像度)の変更
	void BackBufferReSize(const int&size_x, const int&size_y);
	// グラフィックスの解放
	void Release();

	LPDIRECT3DDEVICE9 GetLpDirect3DDevice9();
}