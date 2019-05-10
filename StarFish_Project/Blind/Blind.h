#pragma once

#include"../GameObject/Object/Object.h"
#include"../GameObject/ObjectManager/ObjectManager.h"


class Blind :public Object {
public:
	Blind(D3DXVECTOR2 pos, ObjectManager* obj_mng);
	~Blind() {}
	
	void Update();
	void Draw();
	//void Create(D3DXVECTOR2 pos);
	void Delete();

private:
	float m_speed;

	ObjectManager* m_pobj_mng;
};
