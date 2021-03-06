﻿#include "LoadResource.h"
#include "../Lib/Sound/DirectSound.h"



void Resource::LoadResource() {

	Audio& audio = Audio::getInterface();

	// HACK:もっと簡潔にまとめる

	// テクスチャ読み込み

	// タイトル--------------------------------------------
	// 背景
	Texture::Load("Resource/Texture/Title/title_bg.png");
	// ロゴ
	Texture::Load("Resource/Texture/Title/title_logo.png");
	// 説明画像
	Texture::Load("Resource/Texture/Title/manual.png");
	// ボタン
	Texture::Load("Resource/Texture/UI/title_button01.png");
	Texture::Load("Resource/Texture/UI/title_button02.png");
	Texture::Load("Resource/Texture/UI/title_button03.png");
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
	Texture::Load("Resource/Texture/Enemy/megane_attack_m.png");
	Texture::Load("Resource/Texture/Enemy/megane_move_m.png");

	// ブラインド
	Texture::Load("Resource/Texture/Blind/blind.png");

	// マップ
	Texture::Load("Resource/Texture/Map/bg_clear_01.png");
	Texture::Load("Resource/Texture/Map/bg_clear_02.png");
	Texture::Load("Resource/Texture/Map/bg_clear_03.png");

	// 引数付きのロード(UVをずらしている)
	Texture::LoadEx("Resource/Texture/Map/bg_hero_1.png"
		, 0, 0, 0.f, -0.001f);
	Texture::LoadEx("Resource/Texture/Map/bg_hero_2.png"
		, 0, 0, 0.f, 0.f);
	Texture::LoadEx("Resource/Texture/Map/bg_hero_3.png"
		, 0, 0, 0.f, -0.001f);
	Texture::LoadEx("Resource/Texture/Map/bg_hero_04.png"
		, 0, 0, 0.f, -0.001f);

	// 岩（仮）
	Texture::Load("Resource/Texture/Map/chip_map_image_64.png");
	// 岩清書
	Texture::Load("Resource/Texture/Map/chip-map_image_1.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_2.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_3.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_4.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_5.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_6.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_7.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_8.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_9.png");
	Texture::Load("Resource/Texture/Map/chip-map_image_10.png");

	// 泡エフェクト
	Texture::Load("Resource/Texture/Effect/bubbles.png");

	// GameUI
	// 岩
	// 左
	Texture::LoadEx("Resource/Texture/UI/ui_left.png");
	// 右
	Texture::LoadEx("Resource/Texture/UI/ui_right.png");
	// 黒バー
	Texture::Load("Resource/Texture/UI/ui_black.png");
	// 紫バー
	Texture::Load("Resource/Texture/UI/ui_violet.png");
	// 橙バー
	Texture::Load("Resource/Texture/UI/ui_orange.png");
	// 赤バー
	Texture::Load("Resource/Texture/UI/ui_red.png");

	// しっぱいロゴ
	Texture::Load("Resource/Texture/UI/gameover_logo.png");

	// テクスチャUI
	Texture::Load("Resource/Texture/UI/pause.png");
	//-----------------------------------------------------


	// 勝利シーン------------------------------------------
	// 自機1
	// 勝利モーション（1モーションで計2枚）
	Texture::Load("Resource/Texture/Player/hi_clear_01.png");
	Texture::Load("Resource/Texture/Player/hi_clear_02.png");

	// 自機2
	// 勝利モーション（1モーションで計2枚）
	Texture::Load("Resource/Texture/Player/de_clear_01.png");
	Texture::Load("Resource/Texture/Player/de_clear_02.png");

	// 自機エフェクト
	Texture::Load("Resource/Texture/Effect/clear_eff.png");

	// 背景
	Texture::Load("Resource/Texture/Map/bg_clear_01.png");
	Texture::Load("Resource/Texture/Map/bg_clear_02.png");
	Texture::Load("Resource/Texture/Map/bg_clear_03.png");

	// 勝利UI
	Texture::Load("Resource/Texture/UI/clear_logo.png");
	//-----------------------------------------------------

	// プレイヤーSE
	audio.load({ "Resource/Sound/Player/swim1.wav",
		"Resource/Sound/Player/damage.wav" });

	// ゲームオーバージングル
	audio.load("Resource/Sound/Failed/game_over.wav");

	// クリアシーンのSE
	audio.load({ "Resource/Sound/Clear/clear_effect.wav",
		"Resource/Sound/Clear/player_fly.wav" });

	// BGM
	audio.load({ "Resource/Sound/BGM/main_bgm.wav",
		"Resource/Sound/BGM/title_bgm.wav" });

}
