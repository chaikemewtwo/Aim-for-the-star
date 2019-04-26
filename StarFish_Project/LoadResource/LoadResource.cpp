#include "../LoadResource/LoadResource.h"


void Resource::LoadResouce() {

	// テクスチャ読み込み

	// 自機1
	// 待機状態統合画像（アニメーション込み）
	Texture::Load("Resource/de_wait.png");
	// 泳ぎ状態統合画像（アニメーション込み）
	Texture::Load("Resource/de_swim.png");

	// 敵
	// ウニ
	Texture::Load("Resource/uni.png");

	// マップ
	Texture::Load("Resource/bg_hero_01.png");
	Texture::Load("Resource/bg_hero_02.png");
	Texture::Load("Resource/bg_hero_03.png");

	// 岩
	Texture::Load("Resource/iwa.jpg");
	
}