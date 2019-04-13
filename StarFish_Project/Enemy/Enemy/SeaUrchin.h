#pragma once
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"EnemyBase.h"

// ウニクラス
class SeaUrchin :public EnemyBase{
public:
	SeaUrchin(float x, float y);
	~SeaUrchin() {}

	// 初期化
	void Init()override;

	// 更新
	void Update()override;

	// 描画
	void Draw()override;

	// 遷移
	void ChangeState(StateBase* state)override;

	// 座標ゲッター・セッター
	float GetPosX()override;
	float GetPosY()override;
	float SetPosX(float x)override;
	float SetPosY(float y)override;

	// 速度ゲッター
	float GetSpeed()override;

	// 遷移用タイマーゲッター・セッター
	int GetChangeTimer()override;
	int SetChangeTimer()override;

	// 削除用タイマーゲッター
	int GetDeadTimer()override;

	// 削除フラグゲッター
	bool GetDeadFlag()override;

private:
	Vec2 m_pos;
	float m_speed;
	int m_dead_timer;
	int m_change_timer;
	bool is_dead;
	int enemy_type;
	// 状態を保持する変数
	StateBase* m_pstate_base;
};
