#pragma once
#include<d3dx9.h>
#include<unordered_map>



// オブジェクト(抽象クラス)
class Object {
public:

	Object();

	virtual ~Object() {};

	// ゲッターアクティブ
	bool GetIsActive() {
		return m_is_active;
	}

	// 削除したオブジェクトなどのidを取得に使う
	int GetId() {
		return m_id;
	}
	// 生成したときにidの設定に使う
	void SetId(int id) {
		m_id = id;
	}

	// 仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:

	// オブジェクトのid登録
	void IdRegistr(int id);

	// 位置
	D3DXVECTOR2 m_pos;
	// 生きているか
	bool m_is_active;

	// 生成id入れ
	int m_id;

};