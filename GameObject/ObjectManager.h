#pragma once
#include"./Object.h"
#include<vector>
#include<memory>
#include"../GameObject/PrototypeEnemy/PrototypeEnemyManager.h"



// 全ての管理クラス
class ObjectManager {
public:

	ObjectManager() {

	}

	// 参照返しする
	std::vector<Object*>& GetObjectData() {
		return m_obj;
	}

	void Update();

private:
	// オブジェクト管理クラス(更新時にアドレスを入れる)
	std::vector<Object*>m_obj;
};
