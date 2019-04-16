<<<<<<< HEAD
﻿//#include "../Common/Common.h"
//#include "../LoadResource/LoadResource.h"
//#include "../Player/Star1/Star1.h"
//#include "../Player/Star2/Star2.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	//if (DirectXInit() == false) {
	//	return -1;
	//}
	//Keybord& kb = Keybord::getInterface();
	//
	//// リソース読み込み
	//Resource::LoadResouce();

	//// カーソル消去
	//ShowCursor(FALSE);

	//Star1 star1;
	//Star2 star2;

	//while (ProcessMessage() == true) {
	//	kb.update();

	//	// エスケープキー
	//	if (GetKeyState(VK_ESCAPE) & 0x8000) {
	//		break;
	//	}

	//	star1.Update();
	//	star2.Update();
	//	if (DrawStart() == true)
	//	{
	//		star1.Draw();
	//		star2.Draw();

	//		DrawEnd();
	//	}
	//}

	//Texture::Release();// 追加
	//GraphicsRelease();
	////DirectInputRelease();
	//return 0;
=======
﻿#include"../Lib/D3D/D3D9.h"
#include"../Lib/Window/Window.h"
#include"../Lib/Texture/Texture.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Input/KeyBord.h"
#include"../Enemy/Enemy/EnemyManager.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	// 初期化
	if (DirectXInit() == false) {
		return -1;
	}

	Keybord& kb = Keybord::getInterface();
	EnemyManager e;

	while (ProcessMessage() == true) {
		kb.update();
		if (kb.on(VK_ESCAPE)) {
			break;
		}

		// 描画開始
		if (DrawStart() == true) {

			e.Update();
			e.Draw();

		}
		DrawEnd();
	}

	Texture::Release();
	GraphicsRelease();

	return 0;
>>>>>>> master
}
