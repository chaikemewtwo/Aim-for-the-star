#pragma once
#include"../GameObject/Object/Object.h"
#include<stdio.h>




// 当たり判定付きのオブジェクトを継承するにはCollisionObjectを継承する
class CollisionObject : public Object {
public:

	CollisionObject();

	// 当たった相手を識別する定数
	enum Type {
		PLAYER,
		ENEMY,
		MAX,
	};

	// 仮想デストラクタ
	virtual ~CollisionObject() {};

	// どのObjectを返したのかを返す
	virtual Type GetObjectType()const {
		return MAX;
	}
	// 当たり判定の結果を返す,引数は当たった相手の定数を入れる
	virtual void HitAction(Type type) {};

	// 新しい点を再定義
	D3DXVECTOR2 GetRePoint()const {
		return m_re_point;
	}

protected:

	float m_speed;    // 移動速度
	D3DXVECTOR2 m_re_point; // 新しい点 
};