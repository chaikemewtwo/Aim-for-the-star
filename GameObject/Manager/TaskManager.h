#pragma once
#include<vector>
#include"../Manager/Task.h"

class TaskManager {
public:

	TaskManager(std::vector<Object*>&obj);

	void Update();

private:
	// ここは管理クラスをまとめる所
	std::vector<Task*>m_mng_data;
};