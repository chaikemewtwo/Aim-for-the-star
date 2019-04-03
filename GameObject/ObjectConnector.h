#pragma once
#include"../GameObject/Object.h"
#include<vector>

// 生成して参照を入れろ

// 管理クラスをobectを連結するクラス
class ObjectConnector {
public:

	// 配列の生ポインタを渡すのはいけない。
	ObjectConnector() {};

	// オブジェクトを登録できる
	virtual Object* ObjectEntry(Object&obj) {
		m_obj = &obj;
	}

	// オブジェクトを送る
	Object*GetObjector() {
		return m_obj;
	}

private:
	
	// 注意!参照なので必ず参照を受け取ってから入れる
	Object*m_obj;
};
