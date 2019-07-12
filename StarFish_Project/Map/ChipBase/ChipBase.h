#pragma once
#include"../../CollisionObject/CircleCollisionObject.h"


// ========================
/**
* @file ChipBase.h
* @brief チップの元を生成するファイル
* @author maekawa
*/
// ========================


/**
* @brief チップの基底クラス
*/
class ChipBase :public CircleCollisionObject {
public:

	/**
	* @brief ChipBaseのデフォルトコンストラクタ
	*/
	ChipBase() {
		m_chip_num = 0;
		// 本体のチップは生成されていないようにする
		m_is_active = false;
		m_is_chip_active = false;
		m_is_obj = false;
	}


	/**
	* @brief ChipBaseのコンストラクタ
	* @param[in] chip_num チップ番号
	*/
	ChipBase(int chip_num) {
		m_chip_num = chip_num;
		m_is_active = false;
		m_is_chip_active = false;
		m_is_obj = false;
	}


	/**
	* @brief 更新(Object.h In override)
	*/
	void Update()override {}


	/**
	* @brief 描画(Object.h In override)
	*/
	void Draw()override {}


	/**
	* @brief チップが活動されているかどうかを返す
	* @return bool 
	*/
	bool IsChipActive() {
		return m_is_chip_active;
	}


	/**
	* @brief チップ番号を返す
	* @return int
	*/
	int GetChipNum() {
		return m_chip_num;
	}


	/**
	* @brief オブジェクトかどうかを返す
	* @return bool
	*/
	bool IsEnemy() {
		return m_is_obj;
	}


	/**
	* @brief チップが活動的かをセットする
	* @param[in] is_chip_active チップが活動的か
	*/
	void SetIsChipActive(bool is_chip_active) {
		m_is_chip_active = is_chip_active;
	}


	/**
	* @brief チップ番号を代入するセッター
	* @param[in] chip_num チップ番号
	*/
	void SetChipNum(int chip_num) {
		m_chip_num = chip_num;
	}


	/**
	* @brief オブジェクトかどうかのセッター
	* @param[in] オブジェクトかどうか
	*/
	void SetIsObject(bool is_obj) {
		m_is_obj = is_obj;
	}

protected:

	//! チップの種類番号
	int  m_chip_num;
	//! 存在しているか
	bool m_is_chip_active;
	//! チップではなくオブジェクトかどうか
	bool m_is_obj;             
};

