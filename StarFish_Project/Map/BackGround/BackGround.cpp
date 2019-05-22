#include"BackGround.h"
#include<stdlib.h>
#include"../MapChip/MapChip.h"
#include"../../Lib/D3D/D3D9.h"
#include"../../Lib/Texture/Texture.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Lib/Input/KeyBord.h"




BackGround::BackGround(const std::string&file_name,MapChip*map,SortObject sort_num,float x,float y) {

	// ソート番号代入
	m_sort_object = sort_num;

	m_pos.x = m_pos.y = 0.f;
	
	// 文字列初期化
	for (int i = 0; i < GRAPH_NUM; i++) {
		m_pback_str[i] = '\0';
	}

	// ファイルの読み込み
	BGLoad(file_name);

	// 最初の背景の位置
	m_pos.x = x;
	m_pos.y = y;

	// 今自機がいる場所
	m_current_pos = 0;

	// 画像の位置
	m_connect1_graph = 0;
	m_connect2_graph = 1;
	// 自機の移動初期化
	m_move_pos.x = m_move_pos.y = 0.f;

	// 遷移スクロール位置のポインタを入れる。
	m_pmap = map;
}


void BackGround::Update() {

	MovePosUpdate();
	PosUpdate();
	Scroll();
}


void BackGround::Draw() {

	// 端数分GRAPH_DIFFERENCEでずらす

	// 1枚目描画
	if (m_pback_str[m_connect1_graph] != '\0') {
		Texture::Draw2D(m_pback_str[m_connect1_graph % GRAPH_NUM], -GRAPH_DIFFERENCE, m_pos.y - (float)GRAPH_DIFFERENCE + (-GRAPH_SCALE_H * m_connect1_graph));
	}
	// 2枚目描画
	if (m_pback_str[m_connect2_graph] != '\0') {
		Texture::Draw2D(m_pback_str[m_connect2_graph % GRAPH_NUM], -GRAPH_DIFFERENCE, m_pos.y - (float)GRAPH_DIFFERENCE + (-GRAPH_SCALE_H * m_connect2_graph));
	}
}


void BackGround::BGLoad(const std::string&file_name) {

	// fgets行の終端の改行文字まで読み込み
	FILE*fp;                                  // ストリーム
	//char str_buf[500];                       // 文字列バッファ 

	// ファイルオープン
	fopen_s(&fp,file_name.c_str(), "r");

	// ファイルが読み込まれてない場合
	if (fp == NULL) {
		return;
	}

	// 縦 
	int h = 0;

	// 文字列読み込み、改行まで
	while (fgets(str_load[h], 256, fp) != NULL) {

		if (str_load[h][strlen(str_load[h]) - 1] == '\n') {
			str_load[h][strlen(str_load[h]) - 1] = NULL;
		}

		// 文字列を入れる
		m_pback_str[h] = str_load[h];
			
		h++;
	}

	// ファイルを閉じる
	fclose(fp);
	return;
}


// 背景スクロール
void BackGround::Scroll() {


	// 画面遷移基準
	float screen_up = GRAPH_DIFFERENCE - GRAPH_SCALE_H;
	float screen_down = -GRAPH_DIFFERENCE + GRAPH_SCALE_H;

	// 前にずれているか後ろにずれているかを判断して画像をずらす

	// MEMO 背景は-50 * -50を頂点に描画するので前は50piずらす必要はない
	// 前
	if (-m_pos.y - BG_CHANGE_LINE <= (-GRAPH_SCALE_H) * m_connect1_graph) {
		m_connect2_graph = m_connect1_graph + 1;
	}

	// 前に進んでいる今
	if (-m_pos.y - BG_CHANGE_LINE <= (-GRAPH_SCALE_H) * m_connect2_graph) {
		m_connect1_graph = m_connect2_graph + 1;
	}

	// 下に背景遷移ラインを貼る
	if ((-m_pos.y + GRAPH_SCALE_H - GRAPH_DIFFERENCE) + BG_CHANGE_LINE
		>= (-GRAPH_SCALE_H) * (m_connect1_graph - 1)) {

		m_connect2_graph = m_connect1_graph - 1;
	}

	// ラインより上の場合
	if ((-m_pos.y + GRAPH_SCALE_H - GRAPH_DIFFERENCE) + BG_CHANGE_LINE
		>= (-GRAPH_SCALE_H) * (m_connect2_graph - 1)) {

		m_connect1_graph = m_connect2_graph - 1;
	}

	// デバッグエリア
	{

		// 最後の画像なら下まで行かせないようにする
		if (m_connect1_graph == 0 && -m_pos.y >= 0) {

			m_connect1_graph = 0;
			m_connect2_graph = 1;
		}
	}
}


void BackGround::PosUpdate() {

	// 上下だけ加算
	if (LandOnTheGround() == true) {
		m_pos.y += m_move_pos.y;
	}
}


void BackGround::MovePosUpdate() {

	// 移動ベクトルを入れる
	// プレイヤーの4分の１の速度にする
	m_move_pos = m_pmap->GetMovePos() / 4;// 反対方向に行くので-変換
}


bool BackGround::LandOnTheGround(){

	// 背景のスクロール制限
	if (-m_pmap->GetPos().y > 0.f) {
		return true;
	}
	else if (-m_pmap->GetPos().y <= 0.f) {
		return false;
	}

	return true;
}
