#include<math.h>
#include"EnemyPatrolState.h"
#include"../Enemy/EnemyBase.h"


Patrol* Patrol::GetInstance() {
	static Patrol s_patrol;
	return &s_patrol;
}

void Patrol::Action(EnemyBase* e) {

	D3DXVECTOR2 pos = e->GetPos();

	if (m_max_posx_count > m_posx_count && e->IsLeft() == false) {
		pos.x -= sin(PI * 2 / 120 * m_posx_count)*e->GetSpeed();
	}
	else if (m_max_posx_count > m_posx_count && e->IsLeft() == true) {
		pos.x += sin(PI * 2 / 120 * m_posx_count)*e->GetSpeed();

	}
	
	m_posx_count++;

	if (m_max_posx_count < m_posx_count) {
		m_posx_count = 0;
	}

	e->SetPos(pos);
}