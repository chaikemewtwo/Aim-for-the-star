#pragma once

#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Window/Window.h"
#include"../../CollisionObject/CircleCollisionObject.h"
#include"../../Map/MapChip/MapChip.h"
//#include"../../Player/Player.h"
#include"../../Player/PlayerManager.h"
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


// 敵基底クラス
class EnemyBase :public CircleCollisionObject{
public:
	// コンストラクタ内で共通変数の初期化
	EnemyBase();
	virtual ~EnemyBase() {}

	// 各遷移条件をチェックし、遷移先のStateIdを返す
	virtual StateId StateChangeCheck() = 0;

	// 敵のインスタンスを返す
	virtual EnemyBase* GetInstance();	

	// 引数で指定したStateに遷移
	void ChangeState(StateBase* state);

	// 速度のゲッター
	float GetSpeed();
	
	// 画面の左右どちらかのフラグのゲッター
	bool IsLeft();				

	// オブジェクトタイプのゲッター
	Type GetObjectType()const override {
		return Type::ENEMY;
	}

	// 仮の巡回用の処理　サインカーブ
	float CalcSinCurve() {

		static const float PI = 3.141925f;
	
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

			//player1_distance.y = m_p_player[0]->GetPos().y - m_pos.y;
			//player2_distance.y = m_p_player[1]->GetPos().y - m_pos.y;
			player1_distance.y = m_p_p_mng->GetPosRelay(Player::STAR_1).y - m_pos.y;
			player2_distance.y = m_p_p_mng->GetPosRelay(Player::STAR_2).y - m_pos.y;
		}
		// 自身がプレイヤーよりも下にいる場合
		else if (IsTopPos() == false) {
			player1_distance.y = m_pos.y - m_p_p_mng->GetPosRelay(Player::STAR_1).y;
			player2_distance.y = m_pos.y - m_p_p_mng->GetPosRelay(Player::STAR_2).y;
		}


		// 自身が画面左側にいるとき
		if (m_is_left == true) {

			player1_distance.x = m_p_p_mng->GetPosRelay(Player::STAR_1).x - m_pos.x;
			player2_distance.x = m_p_p_mng->GetPosRelay(Player::STAR_2).x - m_pos.x;
		}
		// 自身が画面右側にいるとき
		else if (m_is_left == false) {

			player1_distance.x = m_pos.x - m_p_p_mng->GetPosRelay(Player::STAR_1).x;
			player2_distance.x = m_pos.x - m_p_p_mng->GetPosRelay(Player::STAR_2).x;
		}

		if (player1_distance.y < player2_distance.y) {
			return m_p_p_mng->GetPosRelay(Player::STAR_1);
		}
		return m_p_p_mng->GetPosRelay(Player::STAR_2);

	}

protected:
	enum EnemyTexture {
		SEAURCHIN_MOVE,		// ウニ画像
		SELLFISH_WAIT,		// ほら貝の待機画像
		SELLFISH_READY,		// ほら貝の攻撃前画像
		SELLFISH_ATTACK,	// ほら貝の攻撃画像
		NAPOREONFISH_MOVE,	// メガネモチノウオの移動画像
		NAPOREONFISH_ATTACK,// メガネモチノウオの攻撃画像
		ENEMY_TEXTURE_MAX
	};


	// 画面外に出たらm_is_activをfalseにする関数
	void CheckEnemyActiv();

	// 自身の位置がプレイヤーの上下どちらかを判定する
	bool IsTopPos();

	// 2体のプレイヤーの、自身とより近い距離を正の数で返す
	D3DXVECTOR2 CalcDistance();

protected:
	int m_power;				// 攻撃力
	int m_delete_timer;			// 削除用タイマー
	bool m_can_move;			// 移動するかのフラグ
	bool m_is_left;				// 画面中央から左右どちらにいるかのフラグ

	float m_angle;				// 描画角度
	float m_center;				// 描画頂点
	int m_anim_change_time;		// 1コマ分の画像の時間
	int m_max_animation;		// 使用するアニメーション数

	std::string m_enemy_texture;// 敵の画像変数
	std::string m_texture_list[EnemyTexture::ENEMY_TEXTURE_MAX];	// 敵の画像リスト
	
	// 画像の分割数　　2分割
	const int TEX_PARTITION_NUM2 = 2;	
	// 描画する画像のXサイズ
	const float TEXTURE_SIZE_X = 0.5f;	
	// 描画する画像のYサイズ
	const float TEXTURE_SIZE_Y = 0.5f;	

	const float WINDOW_CENTER_LINE = Window::WIDTH / 2;

	StateBase* m_p_state_base;	// 状態を保存する変数
	Map* m_p_map;
	//Player* m_p_player[2];
	PlayerManager* m_p_p_mng;	// プレイヤーマネージャー保持
	StateBase* m_pstate_base;	// 状態を保存する変数

	// メガネ用の仮変数《要/修正》
	float m_posx_count;
	const float m_max_posx_count = 720;
};
