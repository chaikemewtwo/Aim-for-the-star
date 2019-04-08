#pragma once
#include"../../Lib/Window/Window.h"
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

	SeaUrchin *seaurchin[Enemy_Max_Num];
};