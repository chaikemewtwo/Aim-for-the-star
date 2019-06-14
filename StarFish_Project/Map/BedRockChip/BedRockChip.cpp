#include"BedRockChip.h"
#include"../../Lib/Texture/TextureBoad2D.h"



BedRockChip::BedRockChip(BedRockChipType bed_rock_chip_type,const D3DXVECTOR2 &pos) {

	//str_buf = str; // 岩盤文字列
	m_pos = pos;   // 位置
	char str_buffer[256];
	// 文字列を選ぶ
	sprintf_s(str_buffer, sizeof(str_buffer), "Resource/Texture/Map/chip-map_image_0%d.png", bed_rock_chip_type + 1);
	bed_rock_chip_name = str_buffer;
	
}

void BedRockChip::Draw(){
	Texture::Draw2D(bed_rock_chip_name.c_str(),m_pos.x,m_pos.y);
}

void BedRockChip::Update(){

}