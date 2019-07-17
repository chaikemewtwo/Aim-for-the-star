#pragma once
//#include "../Player/Player.h"
#include "../Player/PlayerManager.h"


// ロープクラス、最大全長は650×16
class Rope:public Object {
public:
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

	// X方向に対してプレイヤーを引っ張る処理
	// 泳いでる自機がいてもう一方の自機が泳いでないとき、
	// 泳いでない自機に泳いでる自機の移動量を加算
	// 両方の自機が画面外側に向かって泳いでる場合はX方向の移動量を0に
	void ToPlayersPull();

private:
	// ロープの最大の長さ
	static const float MAX_ROPE_LEGTH;

	// ロープ最大全長調整
	static const float ROPE_LEGTH_OFFSET;

	// 描画Y軸調整
	// 自機の中心より少し下に変更、死亡状態でヒモの先端が見えてしまうため
	static const float POS_Y_OFFSET;

private:
	PlayerManager* m_p_player_manager;	// プレイヤー管理クラス
};
