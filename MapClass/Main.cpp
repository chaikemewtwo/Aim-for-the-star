#include"../MapClass/Lib/D3D/D3D9.h"
#include"../MapClass/Lib/Window/Window.h"
#include"../MapClass/Lib/Texture/Texture.h"
#include"../MapClass/Lib/Texture/TextureBoad2D.h"
#include"./Lib/Input/KeyBord.h"
//#include"oxdebugfont.h"
//#include"DebugStage.h"
#include"../MapClass/Resource/Resource.h"
#include"../MapClass/GameScene.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {


	if (DirectXInit() == false) {
		return -1;
	}
	
	//OX::DebugFont::initialize(dev,100,100);

	GameScene * gs = new GameScene;

	ResourceLoad();
	//RenderState();

	while (ProcessMessage() == true) {

		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}

		if (DrawStart() == true) {
			gs->Update();
			gs->Draw();
		}

		DrawEnd();
	}

	//OX::DebugFont::terminate();

	delete gs;

	Texture::Release();
	GraphicsRelease();


	return 0;
}