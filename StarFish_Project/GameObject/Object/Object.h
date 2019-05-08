#pragma once
#include<d3dx9.h>
#include<unordered_map>



// オブジェクト(抽象クラス)
class Object {
public:

	Object();
	// 仮想デストラクタ
	virtual ~Object() {};

	// 仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 描画関数
	void AnimationDraw(int max_animation, int anim_cange_time, int init_anim_num = 0);

	/* ゲッター */
	D3DXVECTOR2 GetPos()const;
	int GetId()const;
	bool IsActive()const;

	/* セッター */
	void SetPos(const D3DXVECTOR2&pos);
	void SetId(int id);

protected:

	D3DXVECTOR2 m_pos;     // 位置
	bool m_is_active;      // Objectが活動しているかの状態変数(活動中true 活動停止false)
	int m_animation_timer; // アニメーションの時間 
	int m_animation_num;   // 現在のアニメーションの数
	
private:
	int m_id;              // 生成id
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
