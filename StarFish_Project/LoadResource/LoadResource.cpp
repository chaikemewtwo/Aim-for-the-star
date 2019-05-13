#include "../LoadResource/LoadResource.h"


void Resource::LoadResouce() {
	// HACK:もっと簡潔にまとめる

	// テクスチャ読み込み

	// ゲームメイン
	// 自機1(デくん、オレンジ)（全て統合画像）
	// 待機状態
	Texture::Load("Resource/Texture/Player/de_wait.png");
	// 立ち待機状態
	Texture::Load("Resource/Texture/Player/de_standing_wait.png");
	// 泳ぎ状態
	Texture::Load("Resource/Texture/Player/de_swim.png");
	// 掴まり状態
	Texture::Load("Resource/Texture/Player/de_hang_wait.png");
	// 投げるモーション
	Texture::Load("Resource/Texture/Player/de_throw.png");
	// 死亡モーション
	Texture::Load("Resource/Texture/Player/de_die.png");

	// 自機2(ヒちゃん、ピンク)（全て統合画像）
	// 待機状態
	Texture::Load("Resource/Texture/Player/hi_wait.png");
	// 立ち待機状態						
	Texture::Load("Resource/Texture/Player/hi_standing_wait.png");
	// 泳ぎ状態							   
	Texture::Load("Resource/Texture/Player/hi_swim.png");
	// 掴まり状態						  
	Texture::Load("Resource/Texture/Player/hi_hang_wait.png");
	// 投げるモーション					   
	Texture::Load("Resource/Texture/Player/hi_throw.png");
	
	// 死亡モーション						
	Texture::Load("Resource/Texture/Player/hi_die.png");
	

	// 敵
	// ウニ
	Texture::Load("Resource/Texture/Enemy/uni.png");
	Texture::Load("Resource/Texture/Enemy/uni_move.png");

	// ほら貝
	Texture::Load("Resource/Texture/Enemy/hora_attack.png");
	Texture::Load("Resource/Texture/Enemy/hora_ready.png");
	Texture::Load("Resource/Texture/Enemy/hora_wait.png");

	// ナポレオンフィッシュ
	Texture::Load("Resource/Texture/Enemy/megane_attack.png");
	Texture::Load("Resource/Texture/Enemy/megane_move.png");


	// マップ
	Texture::Load("Resource/Texture/Map/bg_hero_01.png");
	Texture::Load("Resource/Texture/Map/bg_hero_02.png");
	Texture::Load("Resource/Texture/Map/bg_hero_03.png");

	// 岩（仮）
	Texture::Load("Resource/Texture/Map/chip_map_image_64.png");
	// 岩清書
	Texture::Load("Resource/Texture/Map/chip-map_image_01.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_02.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_03.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_04.png");

	// 泡エフェクト
	Texture::Load("Resource/Texture/Effect/bubbles.png");

	// UI
	Texture::Load("Resource/Texture/UI/UI 岩.png");
	Texture::Load("Resource/Texture/UI/UI　黒.png");
	Texture::Load("Resource/Texture/UI/UI　紫バー.png");
	Texture::Load("Resource/Texture/UI/UI　橙バー.png");


	// 勝利シーン
	// 自機1
	// 勝利モーション（1モーションで計2枚）
	Texture::Load("Resource/Texture/Player/de_crear_01.png");
	Texture::Load("Resource/Texture/Player/de_crear_02.png");

	// 自機2
	// 勝利モーション（1モーションで計2枚）
	Texture::Load("Resource/Texture/Player/hi_crear_01.png");
	Texture::Load("Resource/Texture/Player/hi_crear_02.png");

	// 自機エフェクト
	Texture::Load("Resource/Texture/Effect/crear_eff.png");

	// 背景
	Texture::Load("Resource/Texture/Map/bg_clear_01.png");
	Texture::Load("Resource/Texture/Map/bg_clear_02.png");
	Texture::Load("Resource/Texture/Map/bg_clear_03.png");
}