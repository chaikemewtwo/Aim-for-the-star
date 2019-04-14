#pragma once
#include"../Lib/D3D/D3D9.h"
#include"../Lib/Window/Window.h"
#include<unordered_map>



// オブジェクト(抽象クラス)
class Object {
public:

	// 仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~Object() {};

	// 生きているか
	bool IsActive() {
		return m_is_active;
	}

protected:

	// 位置
	D3DXVECTOR2 m_pos;
	// 拡縮
	D3DXVECTOR2 m_scale;
	// 生きているか
	bool m_is_active;
	// 分割画像のナンバー(画像名がハッシュキー,整数でアニメーションナンバー受け取り)
	int m_div_graph_lists;
	// 画像の最大の数を入れる
	int m_graph_max_num_lists;
};