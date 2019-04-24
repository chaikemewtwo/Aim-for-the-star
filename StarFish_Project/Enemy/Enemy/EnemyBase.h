#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Window/Window.h"
#include"../State/EnemyStateBase.h"
#include"../State/EnemyWaitState.h"


enum EnemyTypeId {
	SeaUrchinId,		// ウニ
	SellFishId,			// ほら貝
	NapoleonFishId,		// ナポレオンフィッシュ
	EnemyTypeMax		// 敵種の最大数
};

// 敵基底クラス
class EnemyBase {
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	virtual void Init() = 0;						// 初期化《変更予定》
	virtual void Update() = 0;						// 更新
	virtual void Draw() = 0;						// 描画
	virtual void ChangeState(StateBase* state) = 0;	// 遷移

	// 画面外に出たらm_is_deadをtrueにする関数
	virtual void  OutScreen();

	// 位置座標のゲッター、セッター
	virtual float GetPosX();
	virtual float GetPosY();

	virtual void SetPosX(float x);
	virtual void SetPosY(float y);

	// 速度のゲッター
	virtual float GetSpeed();

	// 死亡フラグのゲッター
	virtual bool IsDead();

	// タイマーのゲッター
	virtual int GetDeadTimer();

	// 敵種類のゲッター
	virtual int GetEnemyType();

protected:
	// まだObject未反映なので変数はそのまま
	D3DXVECTOR2 m_pos;	// 座標			《削除予定》
	float m_speed;		// 速度			《削除予定》
	int m_dead_timer;	// 削除用タイマー
	bool m_is_dead;		// 削除フラグ	《削除予定》
	int m_enemy_type;	// 敵の種類
};
