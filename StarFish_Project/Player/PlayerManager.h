#pragma once

#include"../../GameObject/ObjectManager/ObjectManager.h"
#include"Player.h"
#include"../ManagerBase/ManagerBase.h"



// プレイヤー管理クラス
class PlayerManager  : public ManagerBase{
public:
	PlayerManager(ObjectManager* obj_mng);
	~PlayerManager();

	void Update();
	void Draw();

	Player* GetPlayerInstance(int player_num);

	// playerのアクセサをID(どちらの自機か)から取得する(中継ぎのような役目)
	float StaminaParcentageRelay(Player::ID_TYPE type);
	D3DXVECTOR2 GetPosRelay(Player::ID_TYPE type);
	void SetPosRelay(Player::ID_TYPE type, D3DXVECTOR2 new_pos);
	D3DXVECTOR2 GetMoveRelay(Player::ID_TYPE type);
	void SetMoveRelay(Player::ID_TYPE type, D3DXVECTOR2 new_move);
	bool IsActiveRelay(Player::ID_TYPE type);
	bool SwimEnableRelay(Player::ID_TYPE type);


	bool PartnerIsThereDirection(Player::ID_TYPE myself, Player::ID_TYPE partner);

private:
	// 自機1のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_1_FIRST_POS;
	// 自機2のゲーム開始時の座標
	static const D3DXVECTOR2 STAR_2_FIRST_POS;

private:
	Player * m_p_list[Player::MAX_TYPE];
};
