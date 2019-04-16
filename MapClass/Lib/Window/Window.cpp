#include"./Window.h"
#include"../D3D/D3D9.h"





// ウィンドウプロシージャ(メッセージをどう解釈するか。)
HRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam) {

	switch (uMsg) {// ウィンドウプロシージャはswitch文で切り分けている。

	case WM_DESTROY:// 一応デストロイする。

		PostQuitMessage(0);
		break;
	}
	// もしかしたらDefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ウィンドウの生成

HWND MakeWindow(int w, int h) {// 他にも入るものがあるかも


	HINSTANCE hi = GetModuleHandle(NULL);// これでインスタンスハンドルを代入できる。

										 // ①ウィンドウクラスを作る。
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hi,
		LoadIcon(NULL,MAKEINTRESOURCE(IDI_APPLICATION)),
		LoadCursor(NULL,IDC_ARROW),
		NULL,// 背景色
		NULL,
		TEXT("DirectX9"),
		NULL,
	};// wcで略す。WNDCLASSEX構造体

	  // ②ウィンドウクラスを登録する。
	if (RegisterClassEx(&wc) == 0) {
		MessageBoxA(0, "ウィンドウクラスの登録に失敗しました。", NULL, MB_OK);
		return 0;
	}

	// ウィンドウのサイズ変更
	// リサイズ
	RECT rect = { 0,0,w,h };

	// ③ウィンドウクラスを設定する。
	HWND hWnd = CreateWindowEx(
		NULL,
		TEXT("DirectX9"),
		TEXT("DirectX9"),
		/*(WS_OVERLAPPEDWINDOW^WS_THICKFRAME) | WS_VISIBLE ,*/WS_POPUP, 
		0,// 引数を無視する。
		0,//CW_USEDDEFAULTにしないと描画してくれない。
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hi,
		NULL);

	if (hWnd == NULL)
	{

		MessageBoxA(0, "ウィンドウの生成に失敗しました。", NULL, MB_OK);
		return 0;// ここ変更
	}

	ShowWindow(hWnd, SW_SHOW);// ウィンドウを必ず表示させるようにする。

	return hWnd;// ここ変更
}

// メモ:
//WNDCLASSEXはどういうウィンドウにするかを設定する物。
// ハンドルは操作する為のもの。

// ウィンドウメッセージの処理]

// 解像度の変更も行いたい


bool ProcessMessage() {

	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

		TranslateMessage(&msg);// 文字列入力系を受け取る関数
		DispatchMessage(&msg);// ウィンドウプロシージャを呼ぶための関数。重要な関数

		if (msg.message == WM_QUIT) {// メッセージがあれば渡す。
			return false;//falseの時はbraekする。終了処理の時に呼ばれる。
		}

		break;
	}
	return true;// メッセージがなかったらtrueを返す。

}


// メモ :
// ウィンドウのメッセージを受け取ったり、投げ返したりする方法。
// MSG等に情報を入れて投げたりする。ゲームではほとんど投げない。ウィンドウのサイズを変える時ぐらい。
// PM_REMOVEはちゃんともう一回回す。
// 昔はもっとcaseが多かった。
// PostQuitMassage関数を呼び出すと一応メッセージを終了してくれる。
// 

bool DrawStart()
{
	// シーンのクリア
	//dev->Clear(0, NULL, D3DCLEAR_TARGET, 0xffffffff, 0.0f, 0);
	dev->Clear(
		0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		NULL,// ここで背景色を変える。
		1.0f, 0
	);

	if (D3D_OK == dev->BeginScene())
	{
		return true;
	}
	return false;
}

// ビューポートの設定は大体ウィンドウのクライアント領域は変えなくて良い
// ので、変える必要はない。


void DrawEnd()
{
	// シーン描画終了
	dev->EndScene();
	// バッファ転送
	dev->Present(NULL, NULL, NULL, NULL);
}



// ウィンドウハンドル(グローバル)
HWND window_handle;

// DirectX関係の初期化。
bool DirectXInit(const int window_w,const int window_h) {

	// ウィンドウの生成が最初
	window_handle = MakeWindow(window_w, window_h);

	if (window_handle == NULL) {

		MessageBoxA(0, "window_handle取得に失敗しました。", NULL, MB_OK);
		return false;
	}

	// D3Dの初期化(ウィンドウ)
	InitD3D(window_handle);

	
	//ShowWindow(window_handle, SW_SHOW);// 追加
	UpdateWindow(window_handle);


	return true;
}

// ウィンドウサイズを変更
void SetWindowSize(const UINT&cx,const UINT&cy) {

	SetWindowPos(window_handle, NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
}

// ウィンドウを中央に移動
void SetWindowCenterMove() {

#define GetMonitorRect(rc) SystemParametersInfo(SPI_GETWORKAREA,0,rc,0)

	RECT rc1;// デスクトップ領域
	RECT rc2;// ウィンドウ領域
	INT cx, cy;// ウィンドウ位置
	INT sx, sy;// ウィンドウサイズ

	// サイズの取得
	GetMonitorRect(&rc1);//デスクトップのサイズ
	GetWindowRect(window_handle, &rc2);// ウィンドウのサイズ

	sx = (rc2.right - rc2.left);// ウィンドウの横幅
	sy = (rc2.bottom - rc2.top);// ウィンドウの高さ

	cx = (((rc1.right - rc1.left) - sx) / 2 + rc1.left);
	cy = (((rc1.bottom - rc1.top) - sy) / 2 + rc1.top);

	SetWindowPos(window_handle, NULL, cx, cy, 0, 0,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
}

// ウィンドウハンドルを返す
HWND GetWindowHandle() {
	return window_handle;
}




