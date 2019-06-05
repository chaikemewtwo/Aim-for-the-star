#include"CollisionObject.h"


CollisionObject::CollisionObject() {
	m_ofset.x = 0.f;
	m_ofset.y = 0.f;
}

// 新しい点を再定義
D3DXVECTOR2 CollisionObject::GetOfset()const {
	return m_ofset;
}