#include"D3D9.h"



namespace D3D9 {
	

	// D3D9パラメータ変数
	LPDIRECT3DDEVICE9 d3d_device9;      // グラフィック関連のデバイスを管理
	LPDIRECT3D9 direct3d9;	            // 環境を設定するためのインターフェース
	D3DPRESENT_PARAMETERS d3d_pp = {};  // グラフィックス設定用 


	bool Init(
		UINT width_size,
		UINT height_size,
		BOOL windowed,
		UINT back_buffer_count) {


		// ウィンドウハンドルのnullチェック
		if (Window::GetWindowHandle() == NULL){

			// ウィンドウハンドルの取得に失敗
			MessageBoxA(0, "GetWindowHandle...Error/Place...D3D9>Init", TEXT("MessageBoxA"), MB_OK);

			// エラーを返す
			return false;
		}

		// ウィンドウハンドル取得
		HWND h_wnd = Window::GetWindowHandle();

		// LPDIRECT3D9は生成した後ほとんど使用しない
		direct3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		// DIRECT3D9のnullチェック
		if (direct3d9 == NULL) {

			// IDirect3D9の生成に失敗
			MessageBoxA(0, "IDirect3D9Create...Error/Place...D3D9>Init", TEXT("MessageBoxA"), MB_OK);

			// エラーを返す
			return false;
		}

		// パーセントパラメーターズのサイズを0にする
		ZeroMemory(&d3d_pp, sizeof(D3DPRESENT_PARAMETERS));

		/* 描画設定 */
		
		// 横の解像度
		d3d_pp.BackBufferWidth = width_size;                         
		// 縦の解像度
		d3d_pp.BackBufferHeight = height_size;						   
		// ディスプレイモード
		d3d_pp.BackBufferFormat = D3DFMT_X8R8G8B8;             
		// バックバッファの数
		d3d_pp.BackBufferCount = back_buffer_count;							  
		// マルチサンプルの数
		d3d_pp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;	  
		// マルチサンプルの品質レベル
		d3d_pp.MultiSampleQuality = 0;						   
		// フロントバッファとバックバッファの切り替え方法
		d3d_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;			   
		// 画面を描画するウィンドウハンドル
		d3d_pp.hDeviceWindow = h_wnd;					       
		// スクリーンモード
		d3d_pp.Windowed = windowed;							       
		// 深度ステンシルバッファがあるかどうか
		d3d_pp.EnableAutoDepthStencil = TRUE;				   
		// ステンシルバッファのフォーマット
		d3d_pp.AutoDepthStencilFormat = D3DFMT_D24S8;		   
		// バックバッファからフロントバッファへ転送時のオプション
		d3d_pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;    
		// フルスクリーンでのリフレッシュレート
		d3d_pp.FullScreen_RefreshRateInHz = 0;				   
		// スワップエフェクトの書き換えタイミング
		d3d_pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; 


		// デバイスの作成
		direct3d9->CreateDevice(
			// ディスプレイアダプターの種類
			D3DADAPTER_DEFAULT,                               
			// デバイスの種類を設定
			D3DDEVTYPE_HAL,                                    
			// デバイスが割り当てられるウィンドウハンドル
			h_wnd,								               
			// デバイス制御の組み合わせ
			D3DCREATE_HARDWARE_VERTEXPROCESSING,               
			// デバイスを設定するためのD3DPRESENT_PARAMETERS構造体のアドレスを渡す
			&d3d_pp,							               
			// LPDIRECT3DDEVICE9のアドレスを渡す
			&d3d_device9						               
		);


		// D3Dデバイスのnullチェック
		if (d3d_device9 == NULL) {

			// デバイスの生成に失敗 
			MessageBoxA(0, "d3d_device9Create...Error/Place...D3D9>Init", TEXT("MessageBoxA"), MB_OK);

			// エラーを返す
			return false;
		}

		// 正常終了
		return true;

		/* MEMO
		デバイスの作成に失敗した場合
		PCの端末がDirectXに対応していない場合がある
		*/
	}


	void SetScreenMode(BOOL is_screen_mode) {

		// スクリーンモードの変更
		d3d_pp.Windowed = is_screen_mode;

		// デバイスの設定を変更する
		d3d_device9->Reset(&d3d_pp);
	}


	void BackBufferReSize(const int&width_size, const int&height_size) {

		// 解像度変更
		d3d_pp.BackBufferWidth = width_size;
		d3d_pp.BackBufferHeight = height_size;

		// デバイスの設定を変更する
		d3d_device9->Reset(&d3d_pp);
	}


	bool DrawStart()
	{
		// シーンのクリア
		d3d_device9->Clear(
			// D3DRECT*の矩形の数
			0,	  
			// ビューポート全体をクリア
			NULL, 
			// Zバッファとステンシルをクリア       
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			// クリアする色情報(背景色)
			NULL, 
			// 深度バッファで使用(未使用なら0,f)
			1.0f, 
			// ステンシルバッファで使用する値(未使用なら0)
			0     
		);

		// シーン描画を開始する
		if (D3D_OK == d3d_device9->BeginScene())
		{
			// 正常終了
			return true;
		}

		// エラー
		return false;
	}


	void DrawEnd()
	{
		// シーン描画終了
		d3d_device9->EndScene();
		// バッファ転送(バックバッファに描画してあるものをフロントバッファに送る)
		d3d_device9->Present(
			  NULL     // 転送元矩形
			, NULL	   // 転送先矩形
			, NULL	   // ウィンドウハンドル
			, NULL);   // 基本NULL
	}


	void Release() {

		// 生成した時と逆の順番で解放
		d3d_device9->Release();
		direct3d9->Release();
	}

	/* GetViewPortやSetViewPortなどもある*/
	
	void ViewPortConfig(D3DVIEWPORT9*d3d_view_port9,DWORD x, DWORD y,DWORD width,DWORD height,FLOAT min_z,FLOAT max_z) {

		// ビューポートのnullチェック
		if (d3d_view_port9 == NULL) {
			return;
		}

		// ビューポートの設定
		d3d_view_port9->X = x;           // X座標
		d3d_view_port9->Y = y;           // Y座標
		d3d_view_port9->Width = width;   // 幅
		d3d_view_port9->Height = height; // 高さ
		d3d_view_port9->MinZ = 0.f;	     // Z深度 : 最小
		d3d_view_port9->MaxZ = 1.f;	     // Z深度 : 最大
	}


	void SetViewPort(D3DVIEWPORT9*view_port) {

		// ビューポートをデバイスにセットできなかったとき
		if (d3d_device9->SetViewport(view_port) != D3D_OK) {
			MessageBoxA(0, "SetViewPort...Error/Place...D3D9>SetViewPort", TEXT("MessageBoxA"), MB_OK);
		}
	}


	HRESULT GetViewPort(D3DVIEWPORT9 d3d_view_port9) {

		// ビューポートのパラメータを受け取る
		HRESULT view_port_parameter = d3d_device9->GetViewport(&d3d_view_port9);

		// 受け取れなかった場合
		if (view_port_parameter != D3D_OK) {
			MessageBoxA(0, "GetViewPort...Error/Place...D3D9>GetViewPort", TEXT("MessageBoxA"), MB_OK);
			return NULL;
		}
		// 正常終了
		return view_port_parameter;
	}


	LPDIRECT3DDEVICE9 GetLpDirect3DDevice9() {
		return d3d_device9;
	}
}
