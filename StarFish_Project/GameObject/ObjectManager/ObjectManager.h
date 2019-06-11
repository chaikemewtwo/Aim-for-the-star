#pragma once
#include<unordered_map>
#include<memory>


/* ～説明書～

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

/* 前方参照 */
class Object;           // オブジェクトクラス
class EnemyManager;     // 敵管理
class MapManager;       // マップ管理
class Player;           // 自機
class CollisionManager; // 衝突管理
class GameUI;           // ゲームメインUI
class Rope;             // ロープ

// 定数の登録順に昇順ソート
enum SortObject {
	BEFORE_BG,
	MAP,
	ROPE,
	PLAYER,
	ENEMY,
	AFTER_BG,
	GAME_UI,
	BLIND,
	MAX,
};

// オブジェクト管理クラス
class ObjectManager {
public:

	ObjectManager();
	~ObjectManager();

	// 更新
	void Update();
	// 描画
	void Draw();

	void ObjectListInit();

	// 要素の追加
	void Entry(Object*obj);
	// 配列の削除(メモリの削除ではない)
	void Exit(unsigned int id);
	// メモリの削除
	void Delete(unsigned int id);
	// クリアフラグを返す
	bool IsClear()const;
	bool IsGameOver()const;

private:

	// 描画用オブジェクトのソート
	void SortDrawObject();

	/* 管理用の配列など */
	std::unordered_map<unsigned int,Object*>m_obj_list;// オブジェクト管理クラス(更新時にアドレスを入れる)
	std::vector<unsigned int>m_used_id_list;           // 使い終わったidを再利用するための配列
	std::vector<Object*>m_draw_obj_list;               // 描画用オブジェクトリスト
	unsigned int m_current_max_id;                     // 現在最大のid

	/* object参照 */
	MapManager * m_p_map_mng;            // マップ管理クラス
	Player * m_p_player[2];              // 自機1,2
	GameUI * m_p_ui;                     // スタミナGameUI
	Rope * m_p_rope;                     // ロープ
	EnemyManager *m_p_enemy_mng;         // 敵管理クラス
	CollisionManager *m_p_collision_mng; // 衝突管理クラス
};
