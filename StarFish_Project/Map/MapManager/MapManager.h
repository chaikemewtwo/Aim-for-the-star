#pragma once



// =========================
/**
* @file MapManager.h(Class)
* @brief マップ関連の管理者
* @author maekawa
*/
// =========================


// 前方参照
class EnemyManager;
class Player;
class Map;
class BackGround;
class ObjectManager;


/**
* @brief マップ関連の管理者
*/
class MapManager {
public:


	/**
	* @brief MapManagerのコンストラクタ
	* @param[out] Player1のポインタ
	* @param[out] Player2のポインタ
	* @param[out] EnemyManagerのポインタ
	* @param[out] ObjectManagerのポインタ 
	*/
	MapManager(Player*star1,Player*star2, EnemyManager*e_mng,ObjectManager*obj_mng);


	/**
	* @brief MapManagerのデストラクタ
	*/
	~MapManager();


	/**
	* @brief MapManagerの更新(Objectのオーバーライド関数)
	*/
	void Update();


	/**
	* @brief MapManagerの描画(Objectのオーバーライド関数)
	*/
	void Draw();


	/**
	* @brief Mapのインスタンスを返す
	* @return Map 同上
	*/
	Map GetMapInstance()const;


	/**
	* @brief マップが最大スクロールかどうかを返す
	* @return bool 同上
	*/
	bool IsMaxMapRange()const;// マップが最大値になったら返す


private:

	// オブジェクトの参照
	Map *m_p_map;        //! マップのポインタ
	BackGround *m_p_bg1; //! 後ろの背景ポインタ
	BackGround *m_p_bg2; //! 前の背景ポインタ
};
