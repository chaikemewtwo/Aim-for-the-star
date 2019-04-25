#pragma once


#include<vector>
#include<memory>
#include<algorithm>
#include<functional>


// 前方宣言
class ObjectManager;

// それぞれ管理クラスをまとめる抽象クラス
class ManagerBase {
public:

	// 必ずコンストラクタでポインタを受け取る
	ManagerBase(ObjectManager*obj_and_mng) {};

	// 更新関数
	virtual void Update() = 0;
	
	// virtualデストラクタ
	virtual ~ManagerBase() {};
	
protected:

	/* インデックス番号で消す場合に使う */

	int m_current_id;            // 現在の最新id番号で使う
	std::vector<int>m_id_lists;  // id番号を入れる箱
};
