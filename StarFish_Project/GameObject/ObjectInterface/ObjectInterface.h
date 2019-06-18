#pragma once
#include"../Object/Object.h"


// オブジェクトを渡す時に間に挟んで隠蔽化を行うクラス


class ObjectInterface {
public:

	ObjectInterface(Object*object);

	D3DXVECTOR2 GetPos();

private:
	Object * m_p_object;
};