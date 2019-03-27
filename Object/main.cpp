
#include"./GameObject/Object.h"
#include"./GameObject/ObjectManager.h"



int main() {

	ObjectManager obj_mng;

	while (true) {

		obj_mng.Update();

		getchar();
	}

}