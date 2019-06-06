#include"./Window.h"
#include"../D3D/D3D9.h"




namespace Window {

	// ウィンドウハンドル
	HWND window_handle;

	// PeekMessageから送られてきたメッセージを処理する
	LRESULT CALLBACK WndProc(
		HWND h_wnd,
		UINT u_msg,
		WPARAM w_param,
		LPARAM l_param);


	HWND MakeWindow(int w, int h) {

		// インスタンスハンドルを代入
		HINSTANCE h_instance = GetModuleHandle(NULL);

	    // ウィンドウクラスを作成
		WNDCLASSEX wnd_class_ex = {
			// WNDCLASSEX構造体のサイズ
			sizeof(WNDCLASSEX),        
			// ウィンドウスタイル
			CS_HREDRAW | CS_VREDRAW,   
			// ウィンドウプロシージャ(メッセージ処理)のアドレス
			WndProc,				   
			// 予備メモリ
			0,						   
			// ウィンドウオブジェクト作成時に作られるメモリサイズ
			0,						   
			// インスタンスハンドル
			h_instance,			       
			// アプリのショートカットなどで使用されるアイコン(いらない場合はNULL) 
			NULL,                      
			// ウィンドウのクライアント上のマウスカーソル
			LoadCursor(NULL,IDC_ARROW),
			// ウィンドウのクライアント領域の背景色 
			NULL,                     
			// メニュー名(メニューがない場合はNULL)
			NULL,					  
			// Windowクラスの名前
			TEXT("DirectX9"),		  
			// タイトルバーで使用されるアイコン
			NULL,
		};

		// ウィンドウクラス構造体を登録
		if (RegisterClassEx(&wnd_class_ex) == 0) {

			MessageBox(0, "WindowClassRegistr...Error", NULL, MB_OK);
			return 0;
		}

		/* ウィンドウのサイズ変更 */

		// リサイズ
		RECT rect = { 0,0,w,h };

		// ウィンドウ作成
		HWND h_wnd = CreateWindow(
			// 登録されているウィンドウクラスの文字列
			TEXT("DirectX9"),			
			// ウィンドウ名
			TEXT("DirectX9"),			
			// ウィンドウスタイルの設定
			(WS_OVERLAPPEDWINDOW^WS_THICKFRAME) | WS_VISIBLE,
			// ウィンドウの表示位置X軸
			0,                          
			// ウィンドウの表示位置Y軸
			0,                          
			// ウィンドウの横幅
			rect.right - rect.left,     
			// ウィンドウの縦幅
			rect.bottom - rect.top,     
			// 親のウィンドウハンドル(なければNULL)
			NULL,                       
			// メニューハンドル(なければNULL)
			NULL,                       
			// インスタンスハンドル
			h_instance,               
			// CREATESTRUCT構造体のポインタ(NULLでいい)
			NULL);                    

		// ウィンドウハンドルのnullチェック
		if (h_wnd == NULL)
		{
			MessageBoxA(0, "CreateWindow...Error", NULL, MB_OK);
			return 0;
		}

		// ウィンドウを表示
		ShowWindow(h_wnd, SW_SHOW);
		// クライアント領域更新
		UpdateWindow(window_handle);

		return h_wnd;
	}


	bool ProcessMessage() {

		// メッセージ受け取り用構造体
		MSG msg;
		
		while (PeekMessage(
			&msg,           // 取得メッセージ
			window_handle,  // ウィンドウハンドル
			0,              // 取得メッセージの最大値
			0,			    // 取得メッセージの最小値
			PM_REMOVE		// 取得メッセージの削除オプション
		)) 
		{
			// 文字列入力系を受け取る
			TranslateMessage(&msg);
			// ウィンドウプロシージャを呼ぶ(重要)
			DispatchMessage(&msg);

			// 終了メッセージの時falseを返す
			if (msg.message == WM_QUIT) {
				return false;
			}

			break;
		}

		// メッセージ送信終了
		return true;
	}

	
	LRESULT CALLBACK WndProc(
		HWND h_wnd,
		UINT u_msg,
		WPARAM w_param,
		LPARAM l_param) {

		switch (u_msg) {
			
		// ウィンドウが破棄される時
		case WM_DESTROY:

			// 終了処理
			PostQuitMessage(0);
			break;
		}

		// 戻り値を返す
		return DefWindowProc(h_wnd, u_msg, w_param, l_param);
	}

	
	bool InitWindow(const int window_w, const int window_h) {

		// ウィンドウの生成が最初
		window_handle = MakeWindow(window_w, window_h);

		if (window_handle == NULL) {

			// エラーメッセージ
			MessageBoxA(0, "GetCreateWindowHandle...Error", NULL, MB_OK);
			return false;
		}
		return true;
	}


	// ウィンドウサイズを変更
	void SetWindowSize(const UINT&cx, const UINT&cy) {

		SetWindowPos(window_handle, NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
	}


	// ウィンドウを中央に移動
	void SetWindowCenterMove() {

		RECT rc1;  // デスクトップ領域
		RECT rc2;  // ウィンドウ領域
		INT cx, cy;// ウィンドウ位置
		INT sx, sy;// ウィンドウサイズ

		/* サイズの取得 */

		//デスクトップのサイズ
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc1, 0);
		// ウィンドウのサイズ
		GetWindowRect(window_handle, &rc2);

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
}


/*
CreateWindow関数
WS_POPUP,// ウィンドウスタイルの設定
*/

/* MEMO
MessageBoxはマルチバイト文字列でしか使えないので注意
unicodeの場合,MessageBoxAを使う
*/

// MEMO :
// ウィンドウのメッセージを受け取ったり、投げ返したりする方法。
// MSG等に情報を入れて投げたりする。ゲームではほとんど投げない。ウィンドウのサイズを変える時ぐらい。
// PM_REMOVEはちゃんともう一回回す。
// 昔はもっとcaseが多かった。
// PostQuitMassage関数を呼び出すと一応メッセージを終了してくれる。


// MEMO:
//WNDCLASSEXはどういうウィンドウにするかを設定する物。
// ハンドルは操作する為のもの。

// ウィンドウメッセージの処理]

// 解像度の変更も行いたい
