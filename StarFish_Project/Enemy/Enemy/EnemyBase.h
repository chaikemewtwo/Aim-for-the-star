#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../CollisionObject/CircleCollisionObject.h"
#include"../../Map/MapChip/MapChip.h"
#include"../../Player/Player.h"
#include"../State/EnemyStateBase.h"


// 敵の状態識別Id
enum StateId {
	WAIT_ID,			// 待機
	SIDEMOVE_ID,		// 横線移動
	VERTICALMOVE_ID,	// 縦線移動
	PATROL_ID,			// 徘徊移動
	ATTACK_READY_ID,	// 攻撃準備
	CHASE_ID,			// 追跡処理
	STATEID_MAX
};

enum EnemyTexture {
	SEAURCHIN_MOVE,		// ウニ画像
	SELLFISH_WAIT,		// ほら貝の待機画像
	SELLFISH_READY,		// ほら貝の攻撃前画像
	SELLFISH_ATTACK,	// ほら貝の攻撃画像
	NAPOREONFISH_MOVE,	// メガネモチノウオの移動画像
	NAPOREONFISH_ATTACK,// メガネモチノウオの攻撃画像
	ENEMY_TEXTURE_MAX	
};


// 敵基底クラス
class EnemyBase :public CircleCollisionObject{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	// 各遷移条件をチェックし、遷移先のStateIdを返す
	virtual StateId StateChangeCheck() = 0;

	virtual void ChangeState(StateBase* state);
	// 敵のインスタンスを返す関数
	virtual EnemyBase* GetInstance();	

	virtual float GetSpeed();
	virtual int GetPower();			
	virtual bool IsLeft();	
	void SetIsLeft(bool is_left) {
		m_is_left = is_left;
	}

	Type GetObjectType()const override {
		return ENEMY;
	}

	// 仮の巡回用の処理　サインカーブ
	float CalcSinCurve() {
	
		float curve = (float)sin(PI * 2 / m_max_posx_count * m_posx_count) *2.5f;
		m_posx_count++;
		if (m_max_posx_count <= m_posx_count) {
			m_posx_count = 0;
		}
		return curve;
	}

	D3DXVECTOR2 CheckCloseTarget() {
		/*
		＊↓簡略化する場所
		 　　CalcDistanceの内容が使えるので、距離を測って近いほうのプレイヤーを返す関数を作る。
		   　CalcDistanceは受け取ったプレイヤーから距離を計算するようにする。
		*/
		D3DXVECTOR2 player1_distance;
		D3DXVECTOR2 player2_distance;

		// 自身がプレイヤーよりも上にいる場合
		if (IsTopPos() == true) {

			player1_distance.y = m_pplayer1->GetPos().y - m_pos.y;
			player2_distance.y = m_pplayer2->GetPos().y - m_pos.y;
		}
		// 自身がプレイヤーよりも下にいる場合
		else if (IsTopPos() == false) {

			player1_distance.y = m_pos.y - m_pplayer1->GetPos().y;
			player2_distance.y = m_pos.y - m_pplayer2->GetPos().y;
		}


		// 自身が画面左側にいるとき
		if (m_is_left == true) {

			player1_distance.x = m_pplayer1->GetPos().x - m_pos.x;
			player2_distance.x = m_pplayer2->GetPos().x - m_pos.x;
		}
		// 自身が画面右側にいるとき
		else if (m_is_left == false) {

			player1_distance.x = m_pos.x - m_pplayer1->GetPos().x;
			player2_distance.x = m_pos.x - m_pplayer2->GetPos().x;
		}

		if (player1_distance.y < player2_distance.y) {
			return m_pplayer1->GetPos();
		}
		return m_pplayer2->GetPos();

	}

protected:
	// 画面外に出たらm_is_activをfalseにする関数
	virtual void OutScreenCheck();
	// 自身の位置がプレイヤーの上下どちらかを判定
	virtual bool IsTopPos();
	// 2体のプレイヤーの、自身とより近い距離を返す
	virtual D3DXVECTOR2 CalcDistance();

protected:
	int m_power;				// 攻撃力
	int m_delete_timer;			// 削除用タイマー
	bool m_no_move;				// 移動するかのフラグ
	bool m_is_left;				// 画面中央から左右どちらにいるかのフラグ

	float m_angle;				// 描画角度
	float m_center;				// 描画頂点
	int m_anim_change_time;		// 1コマ分の画像の時間
	int m_max_animation;		// 使用するアニメーション数
	std::string m_texture_list[ENEMY_TEXTURE_MAX];
	std::string m_enemy_texture;

	const int TEX_PARTITION_NUM2 = 2;	// 画像の分割数　　2分割
	const float TEXTURE_SIZE_X = 0.5f;	// 描画する画像のXサイズ
	const float TEXTURE_SIZE_Y = 0.5f;	// 描画する画像のYサイズ

	StateBase* m_pstate_base;	// 状態を保存する変数
	Map* m_pmap;
	Player* m_pplayer1;
	Player* m_pplayer2;

	float m_posx_count;
	const float m_max_posx_count = 720;
};
