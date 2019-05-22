#include "../LoadResource/LoadResource.h"


void Resource::LoadResouce() {
	// HACK:もっと簡潔にまとめる

	// テクスチャ読み込み

	// タイトル--------------------------------------------
	// 背景
	Texture::Load("Resource/Texture/Title/タイトル　背景.png");
	// ロゴ
	Texture::Load("Resource/Texture/Title/タイトル　ロゴ.png");
	//-----------------------------------------------------


	// ゲームメイン----------------------------------------
	// プレイヤー（全て統合画像）
	// 自機1(デくん、オレンジ)
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

	// 自機2(ヒちゃん、ピンク)
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

	// ヒモ
	Texture::Load("Resource/Texture/Player/himo.png");
	
	// 敵（全て統合画像）
	// ウニ
	Texture::Load("Resource/Texture/Enemy/uni_move.png");

	// ほら貝
	Texture::Load("Resource/Texture/Enemy/hora_attack.png");
	Texture::Load("Resource/Texture/Enemy/hora_ready.png");
	Texture::Load("Resource/Texture/Enemy/hora_wait.png");

	// ナポレオンフィッシュ
	Texture::Load("Resource/Texture/Enemy/megane_attack.png");
	Texture::Load("Resource/Texture/Enemy/megane_move.png");

	// ブラインド
	Texture::Load("Resource/Texture/Blind/blind.png");

	// マップ
	Texture::Load("Resource/Texture/Map/bg_hero_01.png");
	Texture::Load("Resource/Texture/Map/bg_hero_02.png");
	Texture::Load("Resource/Texture/Map/bg_hero_03.png");
	Texture::Load("Resource/Texture/Map/bg_hero_04.png");
	Texture::Load("Resource/Texture/Map/bg_clear_01.png");
	Texture::Load("Resource/Texture/Map/bg_clear_02.png");
	Texture::Load("Resource/Texture/Map/bg_clear_03.png");

	// 岩（仮）
	Texture::Load("Resource/Texture/Map/chip_map_image_64.png");
	// 岩清書
	Texture::Load("Resource/Texture/Map/chip-map_image_01.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_02.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_03.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_04.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_05.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_06.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_07.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_08.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_09.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_10.png");

	// 泡エフェクト
	Texture::Load("Resource/Texture/Effect/bubbles.png");

	// GameUI
	// 岩
	// 左
	Texture::LoadEx("Resource/Texture/UI/ui_lef.png");
	// 右
	Texture::LoadEx("Resource/Texture/UI/ui_rig.png");
	// 黒バー
	Texture::Load("Resource/Texture/UI/ui_bla.png");
	// 紫バー
	Texture::Load("Resource/Texture/UI/ui_vio.png");
	// 橙バー
	Texture::Load("Resource/Texture/UI/ui_ora.png");

	// しっぱいロゴ
	Texture::Load("Resource/Texture/UI/over_logo.png");
	//-----------------------------------------------------


	// 勝利シーン------------------------------------------
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
	//-----------------------------------------------------
}
