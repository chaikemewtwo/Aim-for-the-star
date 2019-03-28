#pragma once
#include"../Object.h"
#include<vector>
#include<memory>
#include<algorithm>
#include<functional>


/* 基底クラスのコンストラクタを使うにはpublicに
   using ManagerData::ManagerData;と書く      */

// それぞれ管理クラスをまとめる抽象クラス
class ManagerData {
public:

	// 生成時に必ずObjectのポインタを渡す
	ManagerData(std::vector<Object*>&object);

	// オブジェクトを追加する
	void ObjectEntry(Object*obj);
	
	// アップデート中の生成物を入れる
	virtual void Entry() {};
	// アップデート中の削除物を入れる
	virtual void Exit() {};
	virtual ~ManagerData() {};
	
	// HACK
	// 外からオブジェクトの参照を受け取って生成する場合に必要
	virtual void ObjectReferencedEntry(std::vector<Object*>&obj) {};

protected:
	
	std::vector<Object*>*m_object;// vectorオブジェクトの参照をここに置く
};


// MEMO
// それぞれidを保存しておき、id++とゲッターとイテレータで
// 消す要素を選択する