#pragma once
#include"../Lib/D3D/D3D9.h"
#include"../Lib/Window/Window.h"

// オブジェクトクラス
class Object {
public:
	
	// 更新
	virtual void Update()=0;

	// 描画
	virtual void Draw()=0;

	~Object() {};
protected:

	// 位置
	D3DXVECTOR2 m_pos;
	// 拡縮
	D3DXVECTOR2 m_scale;
	// 回転
	FLOAT m_angle;
};