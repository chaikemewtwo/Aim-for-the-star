#pragma once
#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"Player.h"
#include"../ManagerBase/ManagerBase.h"
#include"../Map/MapCollider/MapCollider.h"



// プレイヤー管理クラス
class PlayerManager : public ManagerBase{
public:
	PlayerManager(ObjectManager* obj_mng);
	~PlayerManager();

	void Update();

	Player* GetPlayerInstance(int player_num);

	// playerのアクセサをID(どちらの自機か)から取得する(中継のような役目)
	float StaminaParcentageRelay(Player::ID_TYPE type);
	D3DXVECTOR2 GetPosRelay(Player::ID_TYPE type);
	void SetPosRelay(Player::ID_TYPE type, D3DXVECTOR2 new_pos);
	D3DXVECTOR2 GetMoveRelay(Player::ID_TYPE type);
	void SetMoveRelay(Player::ID_TYPE type, D3DXVECTOR2 new_move);
	bool IsActiveRelay(Player::ID_TYPE type);
	bool SwimEnableRelay(Player::ID_TYPE type);

	// myselfのX移動量がmyselfのX座標から見て正or負の方向とmyselfから見てpartnerが正or負の方向を判別
	// 端的に説明するとmyselfが行きたいX方向にpartnerがいるかどうか
	// 正と正、負と負ならtrueが返りそれ以外はfalseが返ります
	// ロープで使用します
	// 引数(比較する側のプレイヤーのポインタ,比較される側のプレイヤーポインタ)
	bool PartnerIsThereDirection(Player::ID_TYPE myself, Player::ID_TYPE partner);


	/* 変更点 auther maekawa */
	CollisionDirectionType GetPlayerCollisionDirectionType(
		Player::ID_TYPE id_type,  
		MoveDirectionType move_dir_type
	);

	void SetPlayerCollisionDirectionType(
		Player::ID_TYPE id_type,
		MoveDirectionType move_dir_type,
		CollisionDirectionType collision_dir_type);
	/* 変更点 auther maekawa */

private:
	// 自機1のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_1_FIRST_POS;
	// 自機2のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_2_FIRST_POS;

private:
	Player * m_p_list[Player::COLLISION_OBJECT_TOTAL];

	// マップ衝突による自機の当たり方向の型 変更点 auther maekawa
	CollisionDirectionType m_player_collision_dir_type[Player::MAX_TYPE][MoveDirectionType::TOTAL_DIR_MOVE];
};
