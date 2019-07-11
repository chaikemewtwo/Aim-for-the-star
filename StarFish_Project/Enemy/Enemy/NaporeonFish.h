#pragma once

#include"EnemyBase.h"


// メガネモチノウオクラス
class NaporeonFish :public EnemyBase {
public:
	NaporeonFish(D3DXVECTOR2 pos, Map* const map, Player* const p1, Player* const p2, bool can_move = false);
	~NaporeonFish()override {}

	void Update()override;
	void Draw()override;
	StateId CheckChangeState()override;

private:
	// ベクトル同士の減算を行う関数
	D3DXVECTOR2 SubVector(const D3DXVECTOR2& vec1, const D3DXVECTOR2& vec2);
	
	// 指定の範囲（三角形）にプレイヤーが入ったかを確認するための関数
	/*
	点と三角形の当たり判定
	第1～3：三角形の各頂点の座標
	第4   ：判定したい相手の座標
	*/
	bool CheckTargetInTheRange(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2, D3DXVECTOR2 vec3, D3DXVECTOR2 target_pos);
};
