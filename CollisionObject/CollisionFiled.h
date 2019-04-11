#pragma once
#include"CollisionObject.h"


// 当たり判定を行う場所
class CollisionFiled : public CollisionObject{
public:

	void Collision();
};