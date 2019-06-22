#include"RockChip.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Map/MapChip/MapChip.h"



RockChip::RockChip(int chip_num,const D3DXVECTOR2 &pos, Map*map) {
	
	// オフセット値設定
	//offset[0].x = 0.f; offset[0].y = 1.f;
	//offset[1].x = 0.f; offset[1].y = 1.f;
	//offset[2].x = 2.f; offset[2].y = -1.f;
	//offset[3].x = 0.f; offset[3].y = 0.f;
	//offset[4].x = 1.f; offset[4].y = 1.f;
	//offset[5].x = 0.f; offset[5].y = 0.f;
	//offset[6].x = 0.f; offset[6].y = 1.f;
	//offset[7].x = 1.f; offset[7].y = -1.f;
	//offset[8].x = 0.f; offset[8].y = 0.f;
	//offset[9].x = 0.f; offset[9].y = 0.f;

	// 最大チップより大きいなら生成失敗
	if (chip_num > MAX_CHIP) {
		return;
	}

	if (map == nullptr) {
		return;
	}

	// ソートオブジェクト代入
	m_sort_object_type = ROCK_CHIP;

	m_pos = pos;                 // 位置
	//m_pos += offset[chip_num]; // 位置を再移動
	char str_buffer[256];        // チップの文字列を入れるchar

	// 文字列を選ぶ
	sprintf_s(str_buffer, sizeof(str_buffer),"Resource/Texture/Map/chip-map_image_%d.png",chip_num);

	// 岩盤ファイル文字列代入
	bed_rock_chip_name = str_buffer;

	// マップインスタンス代入
	m_map = map;
}

void RockChip::Draw(){

	Texture::Draw2D(bed_rock_chip_name.c_str(), m_pos.x, m_pos.y);
}

void RockChip::Update(){

	// マップにそって移動
	m_pos.y += m_map->GetMove().y;
}