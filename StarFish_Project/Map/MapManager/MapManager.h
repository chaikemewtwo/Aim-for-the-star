#pragma once
#include"../../GameObject/Object/Object.h"
#include"../MapCollision/MapCollider.h"
#include"../../ManagerBase/ManagerBase.h"


// =========================
/**
* @file MapManager.h(Class)
* @brief マップ関連の管理者
* @author maekawa
*/
// =========================



// 前方参照
class EnemyManager;
class PlayerManager;
class Map;
class BackGround;
class ObjectManager;


/**
* @brief マップ関連の管理者
*/
class MapManager : public ManagerBase{
public:

	/**
	* @brief MapManagerのコンストラクタ
	* @param[out] Player1のポインタ
	* @param[out] Player2のポインタ
	* @param[out] EnemyManagerのポインタ
	* @param[out] ObjectManagerのポインタ 
	*/
	MapManager(EnemyManager*e_mng,ObjectManager*obj_mng);


	/**
	* @brief MapManagerのデストラクタ
	*/
	~MapManager();


	/**
	* マップの更新
	*/
	void Update();


	/**
	* @brief マップの当たり判定
	*/
	void MapCollision(
		Object*object,
		D3DXVECTOR2&obj_move,
		CollisionDirectionType&collision_dir_type_x,
		CollisionDirectionType&collision_dir_type_y
	);


	/**
	* @brief
	*/
	Map *GetMapInstance();


private:

	//! マップのポインタ
	Map *m_p_map;       

	//! 後ろの背景ポインタ
	BackGround *m_p_bg1; 

	//! 前の背景ポインタ
	BackGround *m_p_bg2; 
};
