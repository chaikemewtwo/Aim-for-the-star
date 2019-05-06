#pragma once
#include"../CollisionObject/CollisionObject.h"



// 円の情報が入ってる当たり判定Objectクラス
class CircleCollisionObject : public CollisionObject{
public:

	// 半径のアクセサ
	float GetRadius() {
		return m_radius;
	}
	void SetRadius(float radius) {
		m_radius = radius;
	}

private:

	// 半径
	float m_radius;
};