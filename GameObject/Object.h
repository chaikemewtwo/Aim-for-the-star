#pragma once
#include"../Lib/D3D/D3D9.h"
#include"../Lib/Window/Window.h"

// オブジェクト(抽象クラス)


class Object {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~Object() {};
	
protected:
	// 位置
	D3DXVECTOR2 m_pos;
	// 拡縮
	D3DXVECTOR2 m_scale;
};