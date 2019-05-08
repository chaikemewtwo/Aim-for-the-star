#pragma once
#include"../CollisionObject/CollisionObject.h"



// 円の情報が入ってる当たり判定Objectクラス
class CircleCollisionObject : public CollisionObject{
public:

	// 半径のアクセサ
	float GetRadius()const {
		return m_radius;
	}

protected:
	// 半径
	float m_radius;
};