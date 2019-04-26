#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../State/EnemyStateBase.h"
#include"../State/EnemyWaitState.h"
#include"../../GameObject/Object/Object.h"


enum EnemyTypeId {
	SeaUrchinId,		// ウニ
	SellFishId,			// ほら貝
	NapoleonFishId,		// ナポレオンフィッシュ
	//EnemyTypeMax		// 敵種の最大数
};

// 敵基底クラス
class EnemyBase :public Object{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	virtual void Init() = 0;						// 初期化《変更予定》
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

	// 削除用タイマーのゲッター
	virtual int GetDeleteTimer();

	// 敵種類のゲッター
	virtual int GetEnemyType();

protected:
	// まだObject未反映なので変数はそのまま
	int m_delete_timer;	// 削除用タイマー
	bool m_is_delete;		// 削除フラグ	《削除予定》
	int m_enemy_type;	// 敵の種類
};
