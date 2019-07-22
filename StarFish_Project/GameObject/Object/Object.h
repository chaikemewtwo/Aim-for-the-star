#pragma once
#include<d3dx9.h>
#include<unordered_map>
#include"../ObjectManager/ObjectManager.h"



// ============================
/**
* @file object.h
* @brief オブジェクトファイル
* @author maekawa
*/
// ============================



/**
* @brief Object 抽象的なオブジェクトクラス
* @detail ゲームで使う描画や更新などの情報を持つクラスに継承して扱う
*/
class Object {
public:


	/**
	* @brief コンストラクタ
	*/
	Object();


	/**
	* @brief 仮想デストラクタ(virtual)
	*/
	virtual ~Object() {};

	
	/**
	* @brief 更新関数(virtual)
	*/
	virtual void Update() = 0;


	/**
	* @brief 描画関数(virtual)
	*/
	virtual void Draw() = 0;


	/**
	* @brief アニメーションのカウントを行う関数
	*/
	void AnimationCount(int max_animation, int anim_cange_time, int init_anim_num = 0);


	/**
	* @brief m_posの位置を取得するゲッター
	* @return D3DXVECTOR2
	*/
	D3DXVECTOR2 GetPos()const;


	/**
	* @brief idを取得するゲッター
	* @return int
	*/
	int GetId()const;


	/**
	* @brief SortObjectを取得するゲッター
	* @return SortObjectType
	*/
	SortObjectType GetSortNum()const;


	/**
	* @brief オブジェクトが活動的かを取得する
	* @return bool
	*/
	bool IsActive()const;


	/**
	* @brief 位置を決めるセッター
	* @param[in] pos オブジェクト位置
	*/
	void SetPos(const D3DXVECTOR2&pos);


	/**
	* @brief オブジェクトのidを決めるセッター
	* @param[in] id オブジェクトID番号
	*/
	void SetId(int id);


protected:

	//! 位置
	D3DXVECTOR2 m_pos;             

	//! Objectが活動しているかの状態変数(活動中true 活動停止false)
	bool m_is_active;              

	//! アニメーションの時間 
	int m_animation_timer;         

	//! 現在のアニメーションの数
	int m_animation_count;         

	//! ソート番号
	SortObjectType m_sort_object_type; 
	
private:

	//! 生成id
	int m_id;
};


/* 円の当たり判定の設定の仕方 */

/*

派生先の設定

GetObjectTypeでCollisionObjectクラスのenumのTypeからどのオブジェクトかのTypeを返す。
理由は当たった相手の情報をもらうため。
Typeにない場合は追加依頼をください

例:

// Playerクラスなら
Type GetObjectType()const override{
return PLAYER
}

// Enemyクラスなら
Type GetObjectType()const override{
return ENEMY;
}

HitAction関数を設定する。
当たった後の処理を設定するため。

例:

void HitAction(Type type)override{

// 別にこの方法じゃなくてもいいよ
// 自機と当たった時
if(type == PLAYER){

}
// 敵と当たった時
else if(type == ENEMY){

}

// こっちでもいい
switch(type){

case PLAYER:

break;

case ENEMY:

break;
}
}
// 最後に半径の設定

m_radius = 50.f

まあコンストラクタらへんで設定したらいい。

// 終わり!

*/
