#pragma once
#include"../Object/GameObject/ManagerData.h"
#include"Enemy.h"



// ここで敵を管理できるようにする
class EnemyManager : public ManagerData {
public:

	EnemyManager(std::vector<Object*>&object);


	// 値がキャスト先まで共通されているか確認する
	// 共通されていないなら、更新した情報を自分に戻す方法を試す

	template<class T>
	// オブジェクト代入
	void EnemyEntry(Object*obj, std::vector<T*>&vec);

	// 特定の位置を削除
	void EnemyExit(std::vector<Object*>&vec, int index);

	// MEMO
	// virtual void (Object*obj)でアップキャストを定義する

	// 生成関数
	void Entry()override {
		EnemyEntry(new Enemy, m_enemy);
		
	}

	void Exit()override {

	}


private:

	// 敵の操作だけ行う
	std::vector<Enemy*>m_enemy;
};

// vectorを入れるvectorを作ればいいかも
