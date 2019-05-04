#include "../LoadResource/LoadResource.h"


void Resource::LoadResouce() {

	// テクスチャ読み込み

	// 自機1
	// 泳ぎ状態統合画像（アニメーション込み）
	Texture::Load("Resource/de_swim.png");

	// 敵
	// ウニ
	Texture::Load("Resource/uni.png");
	Texture::Load("Resource/uni_move.png");

	// サカナ
	Texture::Load("Resource/megane_attack.png");
	Texture::Load("Resource/megane_move.png");

	// 貝
	Texture::Load("Resource/hora_attack.png");
	Texture::Load("Resource/hora_ready.png");
	Texture::Load("Resource/hora_wait.png");

	// マップ
	Texture::Load("Resource/bg_hero_01.png");
	Texture::Load("Resource/bg_hero_02.png");
	Texture::Load("Resource/bg_hero_03.png");

	// 岩
	Texture::Load("Resource/iwa.jpg");
	Texture::Load("Resource/chip_map_image_64.png");
	
}