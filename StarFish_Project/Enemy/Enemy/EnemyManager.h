#pragma once
#include<time.h>
#include"SeaUrchin.h"

// 敵の生成最大数(仮)
const int Enemy_Max_Num = 5;

class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();
	void Update();
	void Draw();
	void Create();
	void Delete();

private:
	// ウニ配列　《要/変更》→敵全体を通した配列に
	std::vector<SeaUrchin*> m_seaurchin;
};
