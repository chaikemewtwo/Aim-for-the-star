#pragma once
#include"../Object/Object.h"


// オブジェクトを渡す時に間に挟んで隠蔽化を行うクラス


class ObjectInterface {
public:


	/**
	* @brief コンストラクタ
	*/
	ObjectInterface(Object*object);


	/**
	* @brief 位置を返す
	* @return D3DXVECTOR2
	*/
	D3DXVECTOR2 GetPos();


private:

	//! オブジェクト
	Object * m_p_object;
};