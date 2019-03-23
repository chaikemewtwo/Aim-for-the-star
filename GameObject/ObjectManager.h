#pragma once
#include"./Object.h"
#include<vector>
#include<memory>
#include"./ManagerAction.h"



// HACK
// Objectを管理するマネージャー
class ObjectManager {
public:

	
	ObjectManager() {
		// 管理クラスはコンストラクタで入れる
		m_mng_action.emplace_back();
	};
	// 外部からオブジェクト群を代入する場合
	ObjectManager(Object*object) {
		m_obj.emplace_back(object);
	}

	// 更新
	void Update();

	// 描画
	void Draw();
	

private:
	// MEMO
	// listにするかvectorにするか
	// オブジェクト入れ
	std::vector<std::unique_ptr<Object>>m_obj;
	// 管理者入れ
	std::vector<std::unique_ptr<ManagerAction>>m_mng_action;
	
};

// MEMO
// Objectをポインタで管理して開始時に渡す方法もあるのかも

// forでエントリーを呼び出す
// 生成クラスを生成するコンストラクタがいる


// グローバルにするならこれ,オブジェクトのポインタ型を返す

/*
namespace ObjectMethod {

	Object* g_obj;

	void _SetObject(Object*object) {
		g_obj = object;
	}

	Object* _GetObject() {

		if (g_obj == nullptr) {
			return nullptr;
		}
		return g_obj;
	}
}
*/
