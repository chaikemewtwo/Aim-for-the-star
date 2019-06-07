#pragma once
#include"../Window/Window.h"


/* DirectXの描画 */

namespace D3D9 {

	/* ---D3Dの初期化--- 

	width_size = 横のバックバッファのサイズ
	height_size = 縦のバックバッファのサイズ
	windowed = ウィンドウモード
	back_buffer_count = バックバッファの数

	*/

	bool Init(
		UINT width_size = 1920,
		UINT height_size = 1080,
		BOOL windowed = TRUE,
		UINT back_buffer_count = 1
	);
	
	/* ---スクリーンモードの変更---

	true = スクリーンモード
	false = フルスクリーンモード

	*/

	void SetScreenMode(BOOL is_screen_mode);

	/* ---解像度の変更--- 

	width_size = 解像度横
	height_size = 解像度縦

	*/

	void BackBufferReSize(const int&width_size, const int&height_size);

	/* ---ビューポートの設定---

	*d3d_view_port9 = ビューポートのポインタ
	x = ビューポートの位置X
	y = ビューポートの位置Y
	width = ビューポートの大きさ横
	height = ビューポートの大きさ縦
	min_z = ビューポートのZ深度最小
	max_z = ビューポートのZ深度最大

	*/

	void ViewPortConfig(
		D3DVIEWPORT9*d3d_view_port9,
		DWORD x,
		DWORD y,
		DWORD width,
		DWORD height,
		FLOAT min_z = 0.f,
		FLOAT max_z = 1.f);

	// 描画領域を伝える
	void SetViewPort(D3DVIEWPORT9*view_port);

	// 現在のビューポートパラメータを受け取る
	HRESULT GetViewPort(D3DVIEWPORT9 d3d_view_port9);

	// デバイスのゲッター
	LPDIRECT3DDEVICE9 GetLpDirect3DDevice9();


	/* 描画の開始と終了 */
	bool DrawStart();
	void DrawEnd();

	// グラフィックスの解放
	void Release();
}