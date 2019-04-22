#pragma once
#include"../State/EnemyStateBase.h"
#include"../State/EnemyWaitState.h"
#include"../State/EnemyChaseState.h"
#include"../State/EnemySideMoveState.h"
#include"../State/EnemyVerticalMoveState.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/D3D/D3D9.h"

enum EnemyTypeId {
	SeaUrchinId,		// ウニ
	SellFishId,			// ほら貝
	NapoleonFishId,		// ナポレオンフィッシュ
	EnemyTypeMax		// 敵種の最大数
};

// 敵基底クラス
class EnemyBase {
public:
	EnemyBase() {}
	virtual ~EnemyBase() {}

	virtual void Init() = 0;						// 初期化
	virtual void Update() = 0;						// 更新
	virtual void Draw() = 0;						// 描画
	virtual void ChangeState(StateBase* state) = 0;	// 遷移

	// 画面外に出たらm_is_deadをtrueにする関数
	virtual void  OutScreen() {
		// 画面外に出たら、削除までの時間をカウントダウン
		if (m_pos.y > WINDOW_H_F || m_pos.x<0 || m_pos.x>WINDOW_W_F) {
			if (m_dead_timer >= 0) {
				m_dead_timer--;
				// 時間が0になったら削除フラグをtrueに
				if (m_dead_timer <= 0) {
					m_is_dead = true;
				}
			}
		}
		// 画面内に戻ったら時間を戻す
		else if (m_pos.y < WINDOW_H_F || m_pos.x>0 || m_pos.x < WINDOW_W_F) {
			m_dead_timer = 60;
		}
	}

	// 位置座標のゲッター、セッター
	virtual float GetPosX() {
		return m_pos.x;
	}

	virtual float GetPosY() {
		return m_pos.y;
	}

	virtual void SetPosX(float x) {
		m_pos.x = x;
	}

	virtual void SetPosY(float y) {
		m_pos.y = y;
	}

	// 速度のゲッター
	virtual float GetSpeed() {
		return m_speed;
	}

	// 死亡フラグのゲッター
	virtual bool IsDead() {
		return m_is_dead;
	}

	// タイマーのゲッター、セッター
	virtual int GetDeadTimer() {
		return m_dead_timer;
	}

	// 敵種類のゲッター
	virtual int GetEnemyType() {
		return m_enemy_type;
	}

protected:
	D3DXVECTOR2 m_pos;	// 座標
	float m_speed;		// 速度
	int m_dead_timer;	// 削除用タイマー
	bool m_is_dead;		// 削除フラグ
	int m_enemy_type;	// 敵の種類
};
