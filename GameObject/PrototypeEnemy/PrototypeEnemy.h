#pragma once
#include"../Object.h"
#include<stdio.h>


// HACK
// オブジェクトの例
// デバッグ中
class Enemy : public Object {
public:

	Enemy() {
		m_num = 0;
	}

	// 更新関数
	void Update()override {
		// 試作です
		printf("Enemy Update\n");
		printf("%d\n", m_num++);
		
	}
	// 描画関数
	void Draw()override {

	}

private:
	// デバッグ変数
	int m_num;
};
