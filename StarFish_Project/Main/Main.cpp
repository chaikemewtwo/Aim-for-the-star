#include"../Lib/D3D/D3D9.h"
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
}
