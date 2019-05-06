#include"../Lib/D3D/D3D9.h"
#include"../Lib/Window/Window.h"
#include"../Lib/Texture/Texture.h"
#include"../Lib/Texture/TextureBoad2D.h"
#include"../Lib/Input/KeyBord.h"
#include"../Enemy/Enemy/EnemyManager.h"
#include"../Player/Star1/Star1.h"
#include"../Player/Star2/Star2.h"
#include"../LoadResource/LoadResource.h"
#include"../Map/MapManager.h"
#include"../SetRenderStateFile/SetRenderStateFile.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	// 初期化
	if (DirectXInit() == false) {
		return -1;
	}

	Keybord& kb = Keybord::getInterface();

	// リソース読み込み
	Resource::LoadResouce();

	// DirectX描画状態の設定s
	SetRenderStateConfig();

	ObjectManager * m_pobj_mng = new ObjectManager;// object管理者

	while (ProcessMessage() == true) {
		// キー入力情報更新
		kb.update();

		// デバッグ用強制終了
		if (kb.on(VK_ESCAPE)) {
			break;
		}

		// 更新
		m_pobj_mng->Update();

		// 描画開始
		if (DrawStart() == true) {

			// 描画
			m_pobj_mng->Draw();

		}
		DrawEnd();
	}

	Texture::Release();
	GraphicsRelease();

	return 0;
}
