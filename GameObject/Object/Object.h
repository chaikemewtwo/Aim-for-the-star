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
	void SetIsActive(bool active) {
		m_is_active = active;
	}


	/* 各アクセサ */

	// 削除したオブジェクトなどのidを取得に使う
	int GetId() const{
		return m_id;
	}
	// 生成したときにidの設定に使う
	void SetId(int id) {
		m_id = id;
	}

	D3DXVECTOR2 GetPos() const{
		return m_pos;
	}
	void SetPos(const D3DXVECTOR2&pos) {
		m_pos = pos;
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