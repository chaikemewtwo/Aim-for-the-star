#include"ObjectInterface.h"



ObjectInterface::ObjectInterface(Object*object) {
	m_p_object = object;
}


D3DXVECTOR2 ObjectInterface::GetPos() {
	return m_p_object->GetPos();
}