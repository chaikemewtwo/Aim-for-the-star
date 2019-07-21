#pragma once

#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"../../Blind/Blind.h"
#include"EnemyBase.h"
#include"../../ManagerBase/ManagerBase.h"


// 敵生成時の指定用定数
enum EnemyType {
	SEAURCHIN = 1,
	NO_MOVE_SEAURCHIN,
	SELLFISH,
	NAPOREONFISH,
	ENEMYTYPE_MAX
};


// 敵管理クラス
class EnemyManager :public ManagerBase{
public:

	EnemyManager(ObjectManager* const obj_mng, PlayerManager* const player_mng);
	~EnemyManager();
	

	void Update()override;	

	// 敵生成関数
	/*
	第1　：敵の生成座標
	第2　：マップのインスタンス(スクロールによる移動に使用)
	第3　：生成する敵の番号を指定
	*/
	void CreateEnemy(const D3DXVECTOR2 pos, Map* const map, const EnemyType enemy_num);

	// ブラインド生成関数
	/*
	第1：生成する座標
	第2：目指す地点(画面外に出るように設定)
	*/
	void CreateBlind(const D3DXVECTOR2 from, const D3DXVECTOR2 goal);

	// 生成されている敵の総数を返す
	int GetEnemyTotal()const;	
	
	// 指定された敵のインスタンスを返す
	EnemyBase* GetEnemyInstance(const int num);

private:
	// 各敵の生存をチェックする
	void CheckDelete();

private:
	std::vector<EnemyBase*> m_enemy_list;	// 生成した敵の配列

	PlayerManager* m_p_player_manager;
	ObjectManager* m_p_obj_manager;				
	Blind* m_p_blind;						
};
