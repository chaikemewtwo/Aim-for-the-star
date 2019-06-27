#include"CollisionObject.h"


CollisionObject::CollisionObject() {
	m_hit_vertex_offset.x = 0.f;
	m_hit_vertex_offset.y = 0.f;
}

// 新しい点を再定義
D3DXVECTOR2 CollisionObject::GetHitVertexOffset()const {
	return m_hit_vertex_offset;
}
