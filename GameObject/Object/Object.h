#pragma once
#include<d3dx9.h>
#include<unordered_map>



// オブジェクト(抽象クラス)
class Object {
public:

	Object();

	virtual ~Object() {};

	// オブジェクトのid登録
	void ObjectIdRedister();

	// ゲッターアクティブ
	bool GetIsActive() {
		return m_is_active;
	}

	// 削除したオブジェクトなどのidを取得に使う
	int GetId(int id) {
		return m_id_lists.at(id);
	}

	// 仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
	

protected:

	// 位置
	D3DXVECTOR2 m_pos;
	// 生きているか
	bool m_is_active;

	// 生成id入れ
	std::vector<int>m_id_lists;
	// 最新id
	static int m_current_id;
};