#pragma once
#include"Object.h"

#include"../Lib/D3D/D3D9.h"
#include"../Lib/Texture/Texture.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Input/KeyBord.h"
//#include"../oxdebugfont.h"
#include"../Player/Player.h"



// 背景クラス
class BackGround : public Object{
public:

	// constexprはコンパイル時定数になる
	static constexpr int GRAPH_NUM = 5;
	// 背景の大きさ
	static constexpr int GRAPH_SCALE_H = 1180;
	static constexpr int GRAPH_SCALE_W = 1920;
	// 背景の端数
	static constexpr int GRAPH_DIFFERENCE = 50;
	// 背景が入れ替わる範囲
	static constexpr float BG_CHANGE_LINE = 10.f;
	// スクロールスピードはプレイヤー速度の3分の1
	//static constexpr int SCROLL_SPEED = (int)SPEED / 3;
	static constexpr float CHIP_SIZE = 128.f;

	BackGround();

	// 自機を取り入れる
	void SetpPlayerPos(Player*player) {

		// 移動ベクトルを入れる
		m_move_pos = player->GetMovePos()/3;
	}

	// 毎回移動を持つ
	void SetMovePos(const D3DXVECTOR2&pos) {

		// プレイヤーの3分の１の速度にする
		m_move_pos = pos / 3;
	}

	// アクセサ
	//D3DXVECTOR2 GetPos() {
	//	return m_pos;
	//}
	//D3DXVECTOR2 GetMovePos() {
	//	return m_move_pos;
	//}
	
	// 背景の読み込み
	//void BGLoad(const std::string&file_name);

	void Update();
	void Draw();

private:

	// 背景スクロール
	void Scroll();

	// 位置更新
	void PosUpdate() {

		// 上下だけ加算
		m_pos.y += m_move_pos.y;
	}

	// 背景文字列
	const char *m_pback_str[GRAPH_NUM];

	// 背景
	D3DXVECTOR2 m_pos;// 背景遷移判定上
	D3DXVECTOR2 m_move_pos;// 移動ベクトル

	// 今いる位置
	int m_now_position;

	// 今の画像
	int m_now_graph;
	int m_next_graph;
};