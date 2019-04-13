#pragma once
#include"../State/StateBase.h"
#include"../State/ChaseState.h"
#include"../State/SideMoveState.h"
#include"../State/VerticalMoveState.h"
#include"../State/WaitState.h"

enum EnemyTypeId {
	SeaUrchinId,		// ウニ
	SellFishId,			// ほら貝
	NapoleonFishId,		// ナポレオン
	EnemyTypeMax		// 敵種の最大数
};

struct Vec2{
	float x;
	float y;
};

// 敵基底クラス
class EnemyBase {
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void ChangeState(StateBase* state) = 0;

	// 位置座標ゲッター、セッター
	virtual float GetPosX() = 0;
	virtual float GetPosY() = 0;
	virtual float SetPosX(float x) = 0;
	virtual float SetPosY(float y) = 0;

	// 速度ゲッター
	virtual float GetSpeed() = 0;

	// フラグ各種ゲッター
	virtual bool GetDeadFlag() = 0;

	// タイマー各種ゲッター、セッター
	virtual int GetDeadTimer() = 0;
	virtual int GetChangeTimer() = 0;
	virtual int SetChangeTimer() = 0;

protected:
	Vec2 m_pos;			// 座標
	float m_speed;		// 速度
	int m_dead_timer;		// 削除用タイマー
	int m_change_timer;	// 遷移用タイマー
	bool is_dead;			// 削除フラグ
	int m_type;			// 敵の種類
private:
};
