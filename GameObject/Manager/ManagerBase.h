#pragma once
#include"../Object.h"
#include<vector>
#include<memory>
#include<algorithm>
#include<functional>



// それぞれ管理クラスをまとめる抽象クラス
class ManagerBase {
public:
	// デフォコン
	ManagerBase() {};
	
	// ゲッターで生成するオブジェクトを一気に渡す
	virtual std::vector<Object*> GetAfterTheBatchEntry()=0;

	// オブジェクトを返す
	virtual Object*GetAfterTheEntry() = 0;

	// アップデート中の削除物を入れる
	virtual void Exit() {};

	virtual ~ManagerBase() {};
protected:

	int update_num;// 生成が更新されたら増える
};
