#pragma once
#include"../GameObject/Object/Object.h"
#include<stdio.h>




// 当たり判定付きのオブジェクトを継承するにはCollisionObjectを継承する
class CollisionObject : public Object {
public:

	// 当たった相手を識別する定数
	enum Type {
		PLAYER,
		ENEMY,
		MAX,
	};

	virtual ~CollisionObject() {};

	// どのObjectを返したのかを返す
	virtual Type GetObjectType() = 0;

	// 当たり判定の結果を返す,引数は当たった相手の定数を入れる
	virtual void HitAction(Type type) {};
protected:
	float m_speed; // 移動速度
};