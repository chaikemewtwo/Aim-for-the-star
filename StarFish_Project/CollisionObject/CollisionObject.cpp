#include"CollisionObject.h"


CollisionObject::CollisionObject() {
	m_offset.x = 0.f;
	m_offset.y = 0.f;
}

// 新しい点を再定義
D3DXVECTOR2 CollisionObject::GetOffset()const {
	return m_offset;
}