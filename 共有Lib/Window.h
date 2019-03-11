#pragma once



#define WINDOW_W 1920
#define WINDOW_H 1080


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

extern HWND window_handle;

bool ProcessMessage();

LPDIRECT3DDEVICE9 InitD3D(HWND hWnd);

bool DirectXInit(const int window_w=WINDOW_W,const int window_h=WINDOW_H);

bool DrawStart();

void DrawEnd();

