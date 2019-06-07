#pragma once
#include<Windows.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

/* ウィンドウ関連 */

namespace Window {

	// ウィンドウデフォルトサイズ
	constexpr float WIDTH = 1920.f;
	constexpr float HEIGHT = 1080.f;

	/* ---ウィンドウの初期化---
	
	window_width = 横のウィンドウサイズ
	window_height = 縦のウィンドウサイズ

	*/
	bool Init(const int window_width = WIDTH, const int window_height = HEIGHT);

	// メッセージ処理
	bool ProcessMessage();

	// その他アクセサ
	void SetSize(const UINT&cx, const UINT&cy);
	void SetCenterMove();
	HWND GetWindowHandle();

	// HACK　まだ使えません
	// フルスクリーンに対応したウィンドウにする
	void FullScreenWindowStyleChange();
}
