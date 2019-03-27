#pragma once
#include"./GameObject/Object.h"




class Enemy : public Object {
public:

	Enemy() {
		num = 0;
	}

	void Update()override {
		printf("Enemy Update\n");
		printf("%d\n", num++);
		
	}
private:

	int num;
};
