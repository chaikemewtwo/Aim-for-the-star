#pragma once
#include"../Object.h"
#include<vector>
#include<memory>
#include<algorithm>
#include<functional>
#include"../ObjectConnector.h"



// それぞれ管理クラスをまとめる抽象クラス
class ManagerBase {
public:
	// デフォコン
	ManagerBase() {};

	// オブジェクトを返す
	virtual void ObjectConnectorEntry(ObjectConnector*ccaa_mng) = 0;

	// アップデート中の削除物を入れる
	virtual void Exit() {};

	virtual ~ManagerBase() {};
protected:

	// 生成が更新されたら増える
	int update_num;

	// 渡す用
	std::vector<Object*>*m_obj;
};

/*

一気に生成して返すBatchEntryはどうか

*/