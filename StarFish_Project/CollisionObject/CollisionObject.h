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

	// 当たり判定頂点をずらす
	D3DXVECTOR2 GetHitVertexOffset()const;

protected:

	// 当たり頂点をずらす 
	D3DXVECTOR2 m_hit_vertex_offset;
};