#pragma once
#include"../Object/Object.h"
#include"../../CollisionObject/CollisionManager.h"
#include<unordered_map>




/* 説明書

       使用例
       
       ①まずObjectの継承を行う。
       オブジェクトを継承する基準はゲーム内で描画されているものならほとんどObjectとして扱う
       
       例:

       {
       // プレイヤーをオブジェクトとして継承
       class Player : public Object
	   }
       
       ②ObjectManagerによる登録
       ObjectManagerをセッター、コンストラクタなどで受け取るなどして、
       登録関数、「Entry(Object*obj)」にオブジェクトを入れて登録
       
       例:

	   {
       Player p;      // 自機のインスタンス
       obj->Entry(p); // Playerを登録
       }
       
       ③Update,Drawなどにそれぞれ処理を入れる。
       
       これでうまく回ったらOK、不具合があったら教えてください

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


class EnemyManager;     // 敵管理の前方参照
class MapManager;       // マップ管理の前方参照
class Star1;            // 自機1の前方参照
class Star2;            // 自機2の前方参照
class CollisionManager; // 衝突管理の前方参照 


// オブジェクト管理クラス
class ObjectManager {
public:

	ObjectManager();

	// 更新
	void Update();
	// 描画
	void Draw();

	// 要素の追加
	void Entry(Object*obj);
	// 配列の削除(メモリの削除ではない)
	void Exit(unsigned int id);

private:

	// オブジェクト管理クラス(更新時にアドレスを入れる)
	std::unordered_map<unsigned int,Object*>m_obj_lists;

	// 使い終わったidを再利用するための配列
	std::vector<unsigned int>m_used_id_lists;
	// 現在最大のid
	unsigned int m_current_max_id;

	/* ここにオブジェクトインスタンスを持つ */

	MapManager * m_pm_mng;    // マップ管理クラス
	Star1 * m_pstar1;         // 自機1
	Star2 * m_pstar2;         // 自機2

	// 敵管理クラス
	EnemyManager *m_pe_mng;
	// 衝突管理クラス
	CollisionManager *m_pcol_mng;
};
