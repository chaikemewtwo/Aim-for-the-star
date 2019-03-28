#pragma once
#include<vector>
#include"../Manager/ManagerData.h"

class TaskManager {
public:

	TaskManager(std::vector<Object*>&obj);

	void Update();

private:
	// ここは管理クラスをまとめる所
	std::vector<ManagerData*>m_mng_data;
};