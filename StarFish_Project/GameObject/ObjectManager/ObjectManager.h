#pragma once
#include<unordered_map>
#include<memory>


/* ---Objectの説明---

   ♦使用例♦

   ①Objectの継承

   class Player,Enemyなど : public Object

   ②ObjectManagerの登録

   オブジェクトマネージャーのポインタ->Entry(登録するオブジェクト)

   ③継承先でUpdateやDrawを定義、処理を内部に入れる

   void Update()override
   void Draw()override

 */

/* ---削除の仕方---

	①ObjectManagerの方で要素削除
	②先のポインタで削除

*/

// 配列型オブジェクトの消し方(敵など)
/*

       // 敵の配列
       auto itr = m_enemy_lists.begin();
       
       for (; itr != m_enemy_lists.end();) {
       
       // 活動を停止したら
       if ((**itr).GetIsActive() == true) {
       
	   // m_obj_mngはObjectManagerのポインタ
       m_obj_mng->Exit((**itr).GetId());
       
       // メモリの削除
       delete (*itr);
       // 敵の要素の削除
       itr = m_enemy_lists.erase(itr);
                  }
           else {
           itr++;
         }
       }
       
       MEMO そのままコピペして使ってください

*/


// 前方参照 
class Object;          
class EnemyManager;    
class MapManager;      
class Player;          
class CollisionManager;
class GameUI;          
class Rope;            


/**
* @enum SortObjectType
* @brief 描画順に昇順ソートする列挙体
*/
enum SortObjectType {
	BEFORE_BG,
	ROPE,
	PLAYER,
	ENEMY,
	ROCK_CHIP,
	AFTER_BG,
	GAME_UI,
	BLIND,
	MAX,
};


/**
* @brief オブジェクト管理クラス
*/
class ObjectManager {
public:


	/**
	* @brief コンストラクタ
	*/
	ObjectManager();


	/**
	* @brief デストラクタ
	*/
	~ObjectManager();


	/**
	* @brief 更新
	*/
	void Update();
	

	/**
	* @brief 描画
	*/
	void Draw();


	/**
	* @brief オブジェクトの登録
	* @param[out] 登録するobjectクラス継承先のオブジェクト
	*/
	void Entry(Object*obj);


	/**
	* @brief 配列の削除(メモリの削除は行わない)
	* @param[in] id 削除id
	*/
	void Exit(unsigned int id);


	/**
	* @brief 指定したオブジェクトの配列の削除(メモリの削除は行わない)
	*/
	void Exit(Object*object);


	/**
	* @brief オブジェクトリストのメモリ削除
	*/
	void MemoryDelete(unsigned int id);


	/**
	* @brief クリアかどうかを取得する
	* @return bool
	*/
	bool IsClear()const;


	/**
	* @brief ゲームオーバーかどうかを取得する
	* @return bool
	*/
	bool IsGameOver()const;


private:


	/**
	* @brief 描画オブジェクトリストの要素を初期化する(メモリの削除は行わない)
	*/
	void InitDrawObjectList();


	/**
	* @brief 描画用オブジェクトリストの登録と昇順ソート
	*/
	void EntryAndSortDrawObject();


private:

	//! オブジェクトリスト
	std::unordered_map<unsigned int,Object*>m_object_list;

	//! 再利用idリスト(使い終わったidを登録するリスト)
	std::vector<unsigned int>m_reuse_id_list;

	//! 描画用オブジェクトリスト
	std::vector<Object*>m_draw_obj_list;

	//! 現在最新id
	unsigned int m_current_the_newest_id;

	//! マップ管理クラスポインタ
	MapManager * m_p_map_mng;

	//! 自機クラスヒトデ1ヒトデ2ポインタ
	Player * m_p_player[2];              

	//! GameUIクラスポインタ
	GameUI * m_p_ui;  

	//! ロープクラスポインタ
	Rope * m_p_rope;                     

	//! 敵管理クラスポインタ
	EnemyManager *m_p_enemy_mng;         

	//! 衝突管理クラスポインタ
	CollisionManager *m_p_collision_mng; 
};
