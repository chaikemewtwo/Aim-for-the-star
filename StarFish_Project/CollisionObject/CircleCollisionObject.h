#pragma once
#include"../CollisionObject/CollisionObject.h"



// 円の情報が入ってる当たり判定クラス
class CircleCollisionObject : public CollisionObject{
public:

	float GetRadius() {
		return m_radius;
	}

private:

	// 半径
	float m_radius;
};