#pragma once
#include<Windows.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

/* ウィンドウ関連 */

// 一旦おいておく
const float PI = 3.1415926535897932384626433832795f;

namespace Window {

	// ウィンドウデフォルトサイズ
	constexpr float WIDTH = 1920.f;
	constexpr float HEIGHT = 1080.f;

	// ウィンドウ生成
	HWND MakeWindow(int w, int h);

	// メッセージ処理
	bool ProcessMessage();

	// ウィンドウ初期化
	bool InitWindow(const int window_w = WIDTH, const int window_h = HEIGHT);

	// その他アクセサ
	void SetWindowSize(const UINT&cx, const UINT&cy);
	void SetWindowCenterMove();
	HWND GetWindowHandle();
}

/*

const float PI = 3.1415926535897932384626433832795f;

constexpr float ToRadian(float deg) {
return (deg / 180.f) * PI;
}
constexpr float ToDegree(float rad) {
return (rad / PI) * 180.f;
}

*/