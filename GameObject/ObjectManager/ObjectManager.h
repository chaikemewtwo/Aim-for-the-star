﻿#pragma once
#include"../Object/Object.h"
#include<memory>

// 動作してる前提

/* 説明書

使用例

オブジェクトの継承を行う。
Objectを継承する基準は描画と更新を行うかどうか

～例～
     class Player : public Object{
	 public:

	 }

	 class Enemy : public Object{
	 public:

	 }

	 使うときはたいていの場合ObjectManagerを引数に入れる。

	 // 自機のコンストラクタ
	 Player(ObjectManager*obj_mng);

生成と削除は下の関数を使う

      Entry関数 = Objectの登録。
      Exit関数  = int型番号の配列を消す。(メモリは削除しない)

	  仮想関数UpdateとDrawについて

	  Updateはオブジェクトの更新
	  Drawはオブジェクトの描画を入れる。

	  class Player : public Object{

	  void Update()override{

	  // Playerの更新情報

	  }

	  void Draw()override{

	  // Playerの描画情報

	  }

*/


// 敵管理の参照
class EnemyManager;

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
	void Exit(int id);

private:

	// オブジェクト管理クラス(更新時にアドレスを入れる)
	std::vector<std::unique_ptr<Object>>m_obj_lists;
	// 当たり判定管理所
	CollisionManager *m_pcol_mng;
	
	// Playerの実体
	Player m_p1;
	Player m_p2;
};
