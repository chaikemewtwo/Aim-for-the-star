#include "../Common/Common.h"
#include "../LoadResource/LoadResource.h"
#include "../Player/Star1/Star1.h"
#include "../Player/Star2/Star2.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	if (DirectXInit() == false) {
		return -1;
	}
	Keybord& kb = Keybord::getInterface();
	
	// リソース読み込み
	Resource::LoadResouce();

	// カーソル消去
	ShowCursor(FALSE);

	Star1 star1;
	Star2 star2;

	while (ProcessMessage() == true) {
		kb.update();

		// エスケープキー
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}

		star1.Update();
		star2.Update();
		if (DrawStart() == true)
		{
			star1.Draw();
			star2.Draw();

			DrawEnd();
		}
	}

	Texture::Release();// 追加
	GraphicsRelease();
	//DirectInputRelease();
	return 0;
}
