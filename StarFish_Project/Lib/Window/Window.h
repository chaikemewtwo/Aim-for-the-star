#pragma once



#define WINDOW_W 1920
#define WINDOW_H 1080

const int WINDOW_W_INT = 1920;
const int WINDOW_H_INT = 1080;

const float WINDOW_W_F = (float)WINDOW_W_INT;
const float WINDOW_H_F = (float)WINDOW_H_INT;


#include<Windows.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")


const float PI = 3.1415926535897932384626433832795f;
constexpr float ToRadian(float deg) {
	return (deg / 180.f) * PI;
}
constexpr float ToDegree(float rad) {
	return (rad / PI) * 180.f;
}


// DirectXの作成の流れ

HWND MakeWindow(int w, int h);

bool ProcessMessage();

LPDIRECT3DDEVICE9 InitD3D(HWND hWnd);

bool DrawStart();

void DrawEnd();

bool DirectXInit(const int window_w = WINDOW_W, const int window_h = WINDOW_H);

// その他アクセサ
void SetWindowSize(const UINT&cx, const UINT&cy);
void SetWindowCenterMove();
HWND GetWindowHandle();

