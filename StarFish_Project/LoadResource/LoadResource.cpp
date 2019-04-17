#include "../LoadResource/LoadResource.h"


void Resource::LoadResouce() {

	// テクスチャ読み込み

	// 自機1
	// 泳ぎ状態統合画像（アニメーション込み）
	Texture::Load("Resource/de_swim.png");

	// 敵
	// ウニ
	Texture::Load("Resource/uni.jpg");
	
}