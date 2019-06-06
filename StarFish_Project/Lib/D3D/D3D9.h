#pragma once
#include"../Window/Window.h"


/* DirectXの描画 */

namespace Graphics {

	/* D3Dの初期化 */
	LPDIRECT3DDEVICE9 InitD3D(HWND hWnd);
	
	/* ---スクリーンモードの変更---

	true = スクリーンモード
	false = フルスクリーンモード

	*/
	void SetScreenMode(bool is_mode);

	/* ---解像度の変更--- 

	size_w = 解像度横
	size_h = 解像度縦

	*/
	void BackBufferReSize(const int&size_w, const int&size_h);

	/* デバイスのアクセサ */
	LPDIRECT3DDEVICE9 GetLpDirect3DDevice9();

	/* 描画の開始と終了 */
	bool DrawStart();
	void DrawEnd();

	// グラフィックスの解放
	void Release();
}