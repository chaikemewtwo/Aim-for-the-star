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
	void AnimationDraw(int max_animation, int anim_cange_time);

	/* ゲッター */
	D3DXVECTOR2 GetPos()const;
	int GetId()const;
	bool IsActive()const;

	/* セッター */
	void SetPos(const D3DXVECTOR2&pos);
	void SetId(int id);

protected:

	D3DXVECTOR2 m_pos;     // 位置
	bool m_is_active;      // Objectが活動しているかの状態変数
	
private:
	int m_id;              // 生成id
	int m_animation_timer; // アニメーションの時間 
	int m_animation_num;   // 現在のアニメーションの数
};