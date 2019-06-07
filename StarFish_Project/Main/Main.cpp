#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Sound/DirectSound.h"
#include"../Lib/Input/KeyBord.h"
#include"../LoadResource/LoadResource.h"
#include"../SetRenderStateFile/SetRenderStateFile.h"
#include"../Scene/SceneManager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {


	// 初期化
	if (Window::Init() == false) {
		return -1;
	}
	if (D3D9::Init() == false) {
		return -1;
	}

	Audio& audio = Audio::getInterface(Window::GetWindowHandle());
	Keybord& kb = Keybord::getInterface();

	// リソース読み込み
	Resource::LoadResource();

	// DirectX描画状態の設定
	SetRenderStateConfig();

	SceneManager* sm = SceneManager::GetInstance();
	sm->Init();

	while (Window::ProcessMessage() == true) {

		// キー入力情報更新
		kb.update();

		// デバッグ用強制終了
		if (kb.on(VK_ESCAPE)) {
			break;
		}

		sm->Update();

		if (sm->IsQuit() == true) {
			break;
		}

		// 描画開始
		if (D3D9::DrawStart() == true) {
			sm->Draw();
		}
		D3D9::DrawEnd();
	}

	Texture::Release();
	D3D9::Release();

	return 0;
}
