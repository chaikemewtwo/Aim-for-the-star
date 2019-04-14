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
	static constexpr int GRAPH_NUMBER = 5;
	// 背景の大きさ
	static constexpr int GRAPH_SCALE_H = 1180;
	static constexpr int GRAPH_SCALE_W = 1920;
	// 背景の端数
	static constexpr int SCREEN_DIFFERENCE = 50;
	// 背景が遷移する範囲
	static constexpr float BG_MOVE_LINE = 10.f;
	// スクロールスピードはプレイヤー速度の3分の1
	static constexpr int SCROLL_SPEED = (int)SPEED / 3;
	static constexpr float CHIP_SIZE = 128.f;

	
	BackGround();

	// 背景スクロール
	void Scroll();

	// 毎回移動を持つ
	void SetMovePos(const D3DXVECTOR2&pos) {
		m_move_pos = pos / 3;// プレイヤーの3分の１の速度にする
	}
	// どこから始めるか
	void SetPos(const D3DXVECTOR2&pos, int now) {
		m_now_position = now;
		m_pos = pos;
	}

	// アクセサ
	D3DXVECTOR2 GetPos() {
		return m_pos;
	}
	D3DXVECTOR2 GetMovePos() {
		return m_move_pos;
	}

	// 位置更新
	void PosUpdate() {
		m_pos += m_move_pos;
	}
	

	// 背景の読み込み
	//void BGLoad(const std::string&file_name);

	void Update();
	void Draw();

private:

	// 背景文字列
	const char *m_pback_str[GRAPH_NUMBER];

	// 背景
	D3DXVECTOR2 m_pos;// 背景遷移判定上
	D3DXVECTOR2 m_move_pos;// 移動ベクトル

	// 今いる位置
	int m_now_position;

	// 今の画像
	int m_now_graph;
	int m_next_graph;
};