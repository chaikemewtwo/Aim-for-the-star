#include"CollisionObject.h"


CollisionObject::CollisionObject() {
	m_re_point.x = 0.f;
	m_re_point.y = 0.f;
}

// 新しい点を再定義
D3DXVECTOR2 CollisionObject::GetRePoint()const {
	return m_re_point;
}