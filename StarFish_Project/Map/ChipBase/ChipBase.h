#pragma once
#include"../../CollisionObject/CircleCollisionObject.h"



// チップ情報をまとめる
class ChipBase :public CircleCollisionObject {
public:

	ChipBase() {
		m_chip_num = 0;
		// 本体のチップは生成されていないようにする
		m_is_active = false;
		m_is_chip_active = false;
		m_is_obj = false;
	}

	ChipBase(int chip_num) {
		m_chip_num = chip_num;
		m_is_active = false;
		m_is_chip_active = false;
		m_is_obj = false;
	}


	void Update()override {}
	void Draw()override {}

	bool IsChipActive() {
		return m_is_chip_active;
	}

	int GetChipNum() {
		return m_chip_num;
	}

	bool IsObject() {
		return m_is_obj;
	}

	void SetIsChipActive(bool is_chip_active) {
		m_is_chip_active = is_chip_active;
	}

	void SetChipNum(int chip_num) {
		m_chip_num = chip_num;
	}

	void SetIsObject(bool is_obj) {
		m_is_obj = is_obj;
	}

protected:
	int  m_chip_num;           // チップの種類番号
	bool m_is_chip_active;     // 存在しているか
	bool m_is_obj;             // チップではなくオブジェクトかどうか
};

