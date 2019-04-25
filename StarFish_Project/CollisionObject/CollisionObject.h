#pragma once
#include"../GameObject/Object/Object.h"
#include<stdio.h>




// 当たり判定付きのオブジェクトを継承するにはCollisionObjectを継承する
class CollisionObject : public Object {
public:

	virtual ~CollisionObject() {};

	// オブジェクト登録関数があればいいかも
	virtual void HitAction() {};

	// 仮想関数のアクセサ
	virtual D3DXVECTOR2 GetPos();
	virtual D3DXVECTOR2 GetMovePos();
	
	virtual void SetPos(D3DXVECTOR2*pos) {};
	virtual void SetMovePos(D3DXVECTOR2*move_pos) {};
private:

	// MEMO move_posはCollisonにいる?
	D3DXVECTOR2 m_move_pos;
};