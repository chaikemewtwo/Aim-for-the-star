#pragma once

#include"EnemyBase.h"


// メガネモチノウオクラス
class NaporeonFish :public EnemyBase {
public:
	NaporeonFish(const D3DXVECTOR2 pos, Map* const map, PlayerManager* const p_mng, bool can_move = false);
	~NaporeonFish()override {}

	void Update()override;
	void Draw()override;
	/*
	メガネモチノウオの遷移
	ChaseState　：索敵範囲内にプレイヤーが入れば追跡に遷移
	PatriolState：追跡以外の場合
	*/
	StateId CheckChangeState()override;

private:
	// ベクトル同士の減算を行う関数
	/*
	第1：計算式の親となるベクトル
	第2：計算式の子になるベクトル
	*/
	inline D3DXVECTOR2 SubVector(const D3DXVECTOR2& vec1, const D3DXVECTOR2& vec2);
	
	// 指定の範囲（三角形）にプレイヤーが入ったかを確認するための関数
	/*
	点と三角形の当たり判定
	第1～3：三角形の各頂点の座標
	第4   ：判定したい相手の座標
	*/
	bool CheckTargetInTheRange(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2, D3DXVECTOR2 vec3, D3DXVECTOR2 target_pos);

private:
	//PlayerManager * m_p_p_mng;
};
