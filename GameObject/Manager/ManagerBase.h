#pragma once
#include"../Object.h"
#include<vector>
#include<memory>
#include<algorithm>
#include<functional>
#include"../ObjectConnector.h"
#include"../GameScene.h"



// それぞれ管理クラスをまとめる抽象クラス
class ManagerBase {
public:

	ManagerBase(ObjectManager*obj_and_mng) {};
	// デフォコン
	ManagerBase() {};

	// 更新関数
	virtual void Update() = 0;
	
	virtual ~ManagerBase() {};
	
protected:
	// インデックス番号で消す
	int m_id;
};
