#pragma once
#include"../Object/GameObject/Object.h"
#include<stdio.h>


// 当たり判定付きのオブジェクトを継承するにはCollisionObjectを継承する
class CollisionObject : public Object {
public:

	// 当たり判定を入れる
	virtual void Collision(){};

	// オブジェクト登録関数があればいいかも
	virtual void HitAction() {};


	void ChackHitCircle(CollisionObject*obj1, CollisionObject*obj2) {

		printf("円の当たり判定");
		obj1->HitAction();
		obj2->HitAction();
	}


private:
	// ここに管理クラスの参照を置く
};