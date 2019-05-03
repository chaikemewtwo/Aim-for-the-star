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



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	// 初期化
	if (DirectXInit() == false) {
		return -1;
	}

	Keybord& kb = Keybord::getInterface();

	// リソース読み込み
	Resource::LoadResouce();

	//dev->SetRenderState(D3DPT_AR)

	// マップ
	MapManager map_m;

	// 自機インスタンス生成
	Star1 star1;
	Star2 star2;

	// 敵インスタンス生成
	EnemyManager e;

	while (ProcessMessage() == true) {
		// キー入力情報更新
		kb.update();

		// デバッグ用強制終了
		if (kb.on(VK_ESCAPE)) {
			break;
		}

		// 描画開始
		if (DrawStart() == true) {
			// マップ
			map_m.Update();
			map_m.Draw();

			// 自機1
			// 更新
			star1.Update();
			// 描画
			star1.Draw();

			// 自機2
			// 更新
			star2.Update();
			// 描画
			star2.Draw();

			// 敵
			// 更新
			e.Update();
			// 描画
			e.Draw();

		}
		DrawEnd();
	}

	Texture::Release();
	GraphicsRelease();

	return 0;
}
