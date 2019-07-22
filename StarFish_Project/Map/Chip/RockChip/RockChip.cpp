#include"RockChip.h"
#include"../../Lib/Texture/TextureBoad2D.h"
#include"../../Map/Map/Map.h"


// オフセット値設定
const D3DXVECTOR2 offset_pos[10] =
{
{ 0.f,1.f },  // 左上
{ 0.f,1.f },  // 右上
{ 0.f,-1.f }, // 左下
{ 0.f,-1.f }, // 右下
{ 0.f,0.f },  // 左
{ 0.f,0.f },  // 右
{ 0.f,1.f },  // 上
{ 0.f,-1.f }, // 下
{ 0.f,0.f },  // 中央
{ 0.f,0.f },  // アンモナイト
};


RockChip::RockChip(int chip_num,const D3DXVECTOR2 &pos, Map*map) {


	// 最大チップより大きいなら生成失敗
	if (chip_num > MAX_CHIP || chip_num <= 0) {
		return;
	}

	if (map == nullptr) {
		return;
	}

	m_is_enemy = false;

	// 生成されている
	m_is_active = true;

	// 生成されている
	m_is_chip_active = true;

	// ソートオブジェクト代入
	m_sort_object_type = ROCK_CHIP;

	// 生成位置を作成
	m_pos = pos;
	
	m_pos += offset_pos[chip_num - 1];
	
	char str_buffer[256];        // チップの文字列を入れるchar

	// チップ番号登録
	this->m_chip_num = chip_num;

	// 文字列を選ぶ
	sprintf_s(str_buffer, sizeof(str_buffer),"Resource/Texture/Map/chip-map_image_%d.png",chip_num);

	// 岩盤ファイル文字列代入
	bed_rock_chip_name = str_buffer;

	// マップインスタンス代入
	m_p_map = map;
}


void RockChip::Draw(){

	Texture::Draw2D(bed_rock_chip_name.c_str(), m_pos.x, m_pos.y,1.0f,1.0f);
}


void RockChip::Update(){

	// マップにそって移動
	m_pos.y += m_p_map->GetMove();
}