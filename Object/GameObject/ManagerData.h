#pragma once
#include"./Object.h"
#include<vector>
#include<memory>
#include<algorithm>
#include<functional>


// 継承する
class ManagerData {
public:

	// アドレスを渡す
	ManagerData(std::vector<Object*>&object) {
		m_object = &object;
		m_id = 0;
	}

	ManagerData() {};

	// 生成関数
	virtual void Entry() {};
	// 消去関数
	virtual void Exit() {};

protected:
	std::vector<Object*>*m_object;
	int m_id;
};




