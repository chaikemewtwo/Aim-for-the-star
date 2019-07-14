#pragma once
//#include "../Player/Player.h"
#include "../Player/PlayerManager.h"


// ロープの最大全長は650×16
class Rope:public Object {
public:
	//Rope(Player* p1,Player* p2);
	Rope(PlayerManager*pm);

	void Update()override;
	void Draw()override;

private:
	// 角度計算
	// ヒモの角度を返します
	float AngleCalc();

	// プレイヤー2体から距離算出
	// プレイヤー同士の距離を返します
	float PlayersRadiusCalc();

	// ロープの長さの比率計算
	// 長さの比率を返します
	float LengthPercentage();

	// プレイヤー2体を一定以上離れなくする
	// ロープで一方を引っ張るようなイメージです
	void PlayersDistanceAdjust();

	// プレイヤー2体を引っ張る処理
	// 泳いでる自機がいてもう一方の自機が泳いでないとき、
	// 泳いでない自機に泳いでる自機の移動量を加算
	// 両方の自機が画面外側に向かって泳いでる場合はX方向の移動量を0に
	void ToPlayersPull();

	// myselfのX移動量がmyselfのX座標から見て正or負の方向とmyselfから見てpartnerが正or負の方向を判別
	// 端的に説明するとmyselfが行きたいX方向にpartnerがいるかどうか
	// 正と正、負と負ならtrueが返りそれ以外はfalseが返ります
	// 引数(比較する側のプレイヤーのポインタ,比較される側のプレイヤーポインタ)
	//bool PartnerIsThereDirection(Player*myself, Player*partner);
	//bool PartnerIsThereDirection(Player*myself, Player*partner);

private:
	// ロープの最大の長さ
	static const float MAX_ROPE_LEGTH;

	// ロープ最大全長調整
	static const float ROPE_LEGTH_OFFSET;

	// 描画Y軸調整
	// 自機の中心より少し下に変更、死亡状態でヒモの先端が見えてしまうため
	static const float POS_Y_OFFSET;

private:
	PlayerManager* m_p_player_mng;

	//Player* m_p1;	// 自機1
	//Player* m_p2;	// 自機2
};
