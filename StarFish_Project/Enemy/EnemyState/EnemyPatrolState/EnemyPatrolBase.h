#pragma once

#include<cmath>
#include<d3dx9.h>
#include"../EnemyStateBase.h"
#include"../../Enemy/EnemyBase.h"


// テストコード
class PatrolBase :public StateBase {
protected:
	void Action(EnemyBase* e)override {

		// 未実装な処理
		//if (m_fast_pos_y == 0) {
		//	m_fast_pos_y = e->GetPos().y;
		//}
		
		//else {
			D3DXVECTOR2 pos = e->GetPos();

			float curve = (float)sin(D3DX_PI * 2 / SINCURVE_COUNT_MAX * m_sin_count) * e->GetSpeed();

			m_sin_count++;

			if (SINCURVE_COUNT_MAX < m_sin_count) {
				m_sin_count = 0;
			}

			pos.x -= curve;
			e->SetPos(pos);
		//}
	}

protected:
	PatrolBase() {
		m_sin_count = 0;
		//m_fast_pos_y = 0;
	}
	~PatrolBase() {}

private:
	float m_sin_count;
	//float m_fast_pos_y;
	const float SINCURVE_COUNT_MAX = 720;
};
