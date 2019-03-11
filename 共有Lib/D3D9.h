#pragma once
#include"Window.h"


// 実体はWindow.hのデバイス作成。
extern LPDIRECT3DDEVICE9 dev;

void GraphicsRelease();

void ResolutionResize(const int&size_x, const int&size_y);