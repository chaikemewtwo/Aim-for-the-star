#pragma once
#include"./Object.h"
#include<vector>
#include<memory>
#include"../EnemyManager.h"


// HACK
// Objectを管理するマネージャー
class ObjectManager {
public:

	
	ObjectManager() {
		// 管理クラスはコンストラクタで入れる
		m_mng_data.emplace_back(new EnemyManager);
	};
	
	void SetObject(Object*object) {
		m_obj.emplace_back(object);
	}

	// 参照を返す
	std::vector<std::unique_ptr<Object>>* GetpObject() {
		return &m_obj;
	}
	
	void Create();
	void Update();
	void Draw();

private:

	// idで要素を探す
	int m_id;
	// MEMO
	// listにするかvectorにするか
	// オブジェクト入れ
	std::vector<std::unique_ptr<Object>>m_obj;
	// 生成クラス群
	std::vector<std::unique_ptr<ManagerData>>m_mng_data;
};

//template<class T>
//// ベクターのコピー
//void Copy(std::vector<T>&obj) {
//	std::copy(m_obj.begin(), m_obj.end(), std::back_inserter(obj));
//}

//// 生成関数
//void Entry(Object*object) {
//	m_obj.emplace_back(object);
//}

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
