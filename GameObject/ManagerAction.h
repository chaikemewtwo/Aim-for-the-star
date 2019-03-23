#pragma once
#include"./Object.h"
#include<vector>
#include<memory>



/* 使い方例

class 生成クラス名 : public ObjectManager{

void Update()override{

Entry(オブジェクト名);

Exit(オブジェクト名)

}

}

この構造のメリットは
生成は継承先で管理できる
つまり生成,削除が外部で呼ばれることはない

この構造のデメリットは
生成クラスを作らなければいけないこと
生成クラスの継承を強要させてしまうこと

*/


// MEMO
// 名前は抽象クラスなので、動詞がいいかどうか

// 生成クラス(抽象クラス)
class ManagerAction {
public:

	ManagerAction() {
		m_id = 0;
	}

	/* オブジェクト生成クラスに派生して使う */

	// 何とか抽象オブジェクトをもってこないといけない
	// 生成関数
	virtual void Entry(Object *object) {
		m_obj.emplace_back(object);
	}

	// 削除関数
	virtual void Exit(Object*object) {
		m_obj.erase(object);
	}

	virtual void Update();


private:
	int m_id;
};