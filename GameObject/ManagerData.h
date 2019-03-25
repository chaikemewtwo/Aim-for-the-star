#pragma once
#include"../Object/GameObject/ObjectManager.h"

// オブジェクトの管理クラスを管理するクラス
// entryを管理クラスごとに呼ぶクラス
class ManagerData {
public:

	ManagerData() {}

	// 生成関数
	void Entry(Object*object) {
		pobject = object;
	}

	// 値を返す
	Object* GetObjectManager() {
		return pobject;
	}

	virtual void Create() {};

private:
	// 参照で受け取って外部に渡す
	Object *pobject;
	std::vector<std::unique_ptr<Object>>m_obj;
};

