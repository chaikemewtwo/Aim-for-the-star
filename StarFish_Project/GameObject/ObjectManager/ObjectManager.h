#pragma once
#include<map>
#include<vector>
#include<memory>
#include <functional>
#include"../../ManagerBase/ManagerBase.h"


// オブジェクト管理者の説明はクラスの下にあります。


/**
* @brief オブジェクトを管理する管理者
*/

// 前方参照 
class Object;          
class EnemyManager;    
class MapManager;      
class PlayerManager;   
class CollisionManager;
class GameUI;          
class Rope;       
class ScrollManager;


/**
* @enum SortObjectType
* @brief 描画順に昇順ソートする列挙体
*/
enum SortObjectType {
	BEFORE_BG,
	ROPE,
	PLAYER,
	ROCK_CHIP,
	ENEMY,
	AFTER_BG,
	BLIND,
	GAME_UI,
	TOTAL,
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
	* @brief 描画用オブジェクトリストの登録と降順ソート
	*/
	void EntryAndSortDrawObject();


	/**
	* @brief ポーズ画面へ移行する
	* @return 移行するなら、trueしないならfalseを返す
	*/
	bool IsMoveToPause();


	/**
	* @brief ポーズ描画
	*/
	void PauseDraw();


private:

	//! 最新id
	int m_current_the_newest_id;

	//! オブジェクトリスト(常に降順ソートを行う)
	std::map<unsigned int,Object*,std::greater<>>m_p_object_list;

	//! 描画用オブジェクトリスト
	std::vector<Object*>m_draw_object_list;

	//! 管理者配列
	std::vector<ManagerBase*>m_p_manager_list;

	//! スクロール管理者
	ScrollManager * m_p_scroll_manager;

	//! 自機クラスヒトデ1ヒトデ2ポインタ
	PlayerManager * m_p_player_manager;

	//! GameUIクラスポインタ
	GameUI * m_p_ui;  

	//! ロープクラスポインタ
	Rope * m_p_rope;                

	//! ポーズフラグ
	bool m_is_pause;
};


// MEMO
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
②各管理者で参照を受け取っておき、各管理者側でメモリ削除

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

