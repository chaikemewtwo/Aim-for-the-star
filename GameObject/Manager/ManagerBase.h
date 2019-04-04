#pragma once
#include"../Object.h"
#include<vector>
#include<memory>
#include<algorithm>
#include<functional>


// 前方宣言
class ObjectManagerToDoRegistr;

// それぞれ管理クラスをまとめる抽象クラス
class ManagerBase {
public:

	// 必ずコンストラクタでポインタを受け取る
	ManagerBase(ObjectManagerToDoRegistr*obj_and_mng) {};

	// 更新関数
	virtual void Update() = 0;
	
	// virtualデストラクタ
	virtual ~ManagerBase() {};
	
protected:
	// インデックス番号で消す場合に使う
	int m_id;                    // 登録するid番号
	std::vector<int>m_id_lists;  // id番号が入ってるもの
};
