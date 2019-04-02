#pragma once
#include"../GameObject/Object.h"
#include<vector>



// 管理クラスを変換コネクトするクラス
// 関連連結クラスともいう
class ObjectConnector {
public:

	// 初期化時にアドレスを受け取る
	ObjectConnector(std::vector<Object*>&vector) {
		m_obj = &vector;
	}

	// オブジェクトを登録できる。
	void ObjectEntry(Object&obj) {
		m_obj->emplace_back(&obj);
	}

private:
	
	// 注意!参照なので必ず参照を受け取ってから
	// 入れる
	// 関連データを入れる
	std::vector<Object*>*m_obj;
};
