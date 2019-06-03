#include"BedRockChip.h"
#include"../StarFish_Project/Lib/Texture/TextureBoad2D.h"



BedRockChip::BedRockChip(const std::string&str,const D3DXVECTOR2 &pos) {

	str_buf = str; // 岩盤文字列
	m_pos = pos;   // 位置
}

void BedRockChip::Draw(){
	Texture::Draw2D(str_buf.c_str(),m_pos.x,m_pos.y);
}

void BedRockChip::Update(){

}