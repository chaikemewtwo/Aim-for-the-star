#include"Blind.h"


Blind::Blind(D3DXVECTOR2 pos, ObjectManager* obj_mng) {
	m_pos = pos;
	m_pobj_mng = obj_mng;
	m_pobj_mng->Entry(this);
}

void Blind::Update() {
	
}

void Blind::Draw() {
	// ブラインドの小魚を描画(アニメーションあり)
}

void Blind::Delete() {
	if (IsActive() == false) {
		m_pobj_mng->Exit(this->GetId());
	}
}
