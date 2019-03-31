#pragma once
#include"../Object.h"



// オブジェクトの例
class Enemy : public Object {
public:

	Enemy() {
		//num = 0;
	}
	// 更新関数
	void Update()override {
		//printf("Enemy Update\n");
		//printf("%d\n", num++);
		
	}
	// 描画関数
	void Draw()override {

	}

private:
	//int num;
};
