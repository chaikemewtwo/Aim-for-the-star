#pragma once
#include"../Map/Object.h"



// 位置を外部に漏らさず繋げてくれる
class PosConnector : public Object{
public:

	virtual void SetPos(D3DXVECTOR2 &pos) {};

	virtual D3DXVECTOR2 GetPos() {
		D3DXVECTOR2 DummyVec2 = {};
		 return DummyVec2;
	};

	virtual void SetMovePos(D3DXVECTOR2&move_pox) {};

	virtual D3DXVECTOR2 GetMovePos() {
		D3DXVECTOR2 DummyVec2 = {};
		return DummyVec2;
	}

	virtual ~PosConnector() {};
};