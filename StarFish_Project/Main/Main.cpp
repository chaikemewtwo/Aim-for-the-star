#include"../Lib/D3D/D3D9.h"
#include"../Lib/Window/Window.h"
#include"../Lib/Texture/Texture.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Sound/DirectSound.h"
#include"../Lib/Input/KeyBord.h"
#include"../LoadResource/LoadResource.h"
#include"../SetRenderStateFile/SetRenderStateFile.h"
#include"../Scene/SceneManager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	// 初期化
	if (DirectXInit() == false) {
		return -1;
	}

	Audio& audio = Audio::getInterface(GetWindowHandle());
	Keybord& kb = Keybord::getInterface();

	// リソース読み込み
	Resource::LoadResource();

	// DirectX描画状態の設定
	SetRenderStateConfig();

	SceneManager* sm = SceneManager::GetInstance();
	sm->Init();
	

	while (ProcessMessage() == true) {
		// キー入力情報更新
		kb.update();

		// デバッグ用強制終了
		if (kb.on(VK_ESCAPE)) {
			break;
		}

		

		// 描画開始
		if (DrawStart() == true) {

			sm->Update();

		}
		DrawEnd();
	}

	Texture::Release();
	GraphicsRelease();

	return 0;
}
