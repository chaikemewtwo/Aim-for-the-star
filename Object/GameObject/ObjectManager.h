#pragma once
#include"./Object.h"
#include<vector>
#include<memory>
#include"./ManagerData.h"
#include"../EnemyManager.h"


// 全ての管理クラス
class ObjectManager {
public:

	ObjectManager() {
		m_mng_data.emplace_back(new EnemyManager(m_obj));
	}

	void Update();

private:
	// オブジェクト管理クラス(更新時にアドレスを入れる)
	std::vector<Object*>m_obj;
	// 生成クラスの管理クラス
	std::vector<std::unique_ptr<ManagerData>>m_mng_data;
	//std::reference_wrapper
};
