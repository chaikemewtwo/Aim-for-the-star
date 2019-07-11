#pragma once

#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../../Blind/Blind.h"
#include"EnemyBase.h"


// 敵生成時の指定用定数
enum EnemyType {
	SEAURCHIN = 1,
	NO_MOVE_SEAURCHIN,
	SELLFISH,
	NAPOREONFISH,
	ENEMYTYPE_MAX
};


class EnemyManager {
public:
	EnemyManager(ObjectManager* const obj_mng);
	~EnemyManager();
	

	void Update();	

	// 敵生成関数
	/*
	第1　：敵の生成座標
	第2　：マップのインスタンス(スクロールによる移動に使用)
	第3,4：プレイヤーのインスタンス(追跡、索敵に使用)
	第5　：生成する敵の番号を指定
	*/
	void CreateEnemy(D3DXVECTOR2 pos, Map* const map, PlayerManager* const p_mng, const EnemyType enemy_num);

	// ブラインド生成関数
	/*
	第1：生成する座標
	第2：目指す地点(画面外に出るように設定)
	*/
	void CreateBlind(D3DXVECTOR2 from, D3DXVECTOR2 goal);

	// 生成されている敵の総数を返す
	int GetEnemyTotal()const;	
	
	// 指定された敵のインスタンスを返す
	EnemyBase* GetEnemyInstance(int num);

private:
	// 各敵の生存をチェックする
	void CheckDelete();

private:
	std::vector<EnemyBase*> m_enemy_list;	// 生成した敵の配列

	ObjectManager* m_p_obj_mng;				
	Blind* m_p_blind;						
};
