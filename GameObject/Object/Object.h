#pragma once
#include<d3dx9.h>
#include<unordered_map>



// オブジェクト(抽象クラス)
class Object {
public:

	// 仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~Object() {};

protected:

	// 位置
	D3DXVECTOR2 m_pos;
	// 拡縮
	D3DXVECTOR2 m_scale;
	// 移動速度
	float m_speed;
};