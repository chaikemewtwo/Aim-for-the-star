
#include"D3D9.h"

// D3Dの初期化

// ① 
LPDIRECT3D9 direct3d9;
LPDIRECT3DDEVICE9 dev;// externの実体

// ②パラメーター
D3DPRESENT_PARAMETERS pp = {};

LPDIRECT3DDEVICE9 InitD3D(HWND hWnd) {// デバイス

	direct3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (direct3d9 == NULL) {

		MessageBoxA(0, "IDirect3D9の作成に失敗しました", NULL, MB_OK);
	}

	ZeroMemory(&pp, sizeof(D3DPRESENT_PARAMETERS));

	// ここの設定は描画に必要

	// パラメーターズは全部設定
	pp.BackBufferWidth = 0;// 解像度
	pp.BackBufferHeight = 1088;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = hWnd;
	pp.Windowed = TRUE;// 追加
	pp.EnableAutoDepthStencil = TRUE;
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	pp.Windowed = TRUE;// フルスクリーンモード
	pp.FullScreen_RefreshRateInHz = 0;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	// ③
	direct3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&pp, &dev
	);

	if (direct3d9 == NULL) {

		MessageBoxA(0, "デバイスの生成に失敗しました。", NULL, MB_OK);
		return 0;
	}

	return dev;
}

// 解像度の変更(今は起動していないので注意)
void ResolutionResize(const int&size_x, const int&size_y) {
	pp.BackBufferWidth = size_x;
	pp.BackBufferHeight = size_y;
}

// 解放
void GraphicsRelease() {

	dev->Release();
	direct3d9->Release();
}
