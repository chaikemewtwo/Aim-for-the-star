#pragma once
#include"../GameObject/Object/Object.h"
#include<stdio.h>



// ==================================
/**
* @file CollisionObject.h
* @brief 衝突用オブジェクトファイル
* @author maekawa
*/
// ==================================



/**
* @brief 衝突オブジェクトクラス(抽象クラス)
* @detail 当たり判定を付けるなら衝突用オブジェクトを継承させる
*/
class CollisionObject : public Object {
public:

	/**
	* @enum Type
	* @brief 衝突した相手を識別する列挙体
	*/
	enum Type {
		COLLISION_OBJECT_PLAYER,
		COLLISION_OBJECT_ENEMY,
		COLLISION_OBJECT_TOTAL,
	};

public:


	/**
	* @brief コンストラクタ
	*/
	CollisionObject();


	/**
	* @brief 仮想デストラクタ(virtual)
	*/
	virtual ~CollisionObject() {};


	/**
	* @brief どのObjectと接触したのかを返す(virtual)
	* @return Type
	*/
	virtual Type GetCollisionObjectType()const {
		return COLLISION_OBJECT_TOTAL;
	}


	/**
	* @brief 衝突後の処理を行う
	* @param[in] type 衝突したオブジェクトタイプを返す
	*/
	virtual void HitAction(Type type) {};


	/**
	* @brief 当たり判定用の頂点をずらす
	* @return D3DXVECTOR2 衝突頂点
	*/
	D3DXVECTOR2 GetHitVertexOffset()const;


protected:
	float m_speed;
	//! 当たり頂点をずらす 
	D3DXVECTOR2 m_hit_vertex_offset;
};