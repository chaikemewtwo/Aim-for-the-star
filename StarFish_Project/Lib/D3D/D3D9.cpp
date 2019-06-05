
#include"D3D9.h"






namespace Graphics {
	

	// D3Dパラメータ変数
	LPDIRECT3DDEVICE9 d3d_device9;      // グラフィック関連のデバイスを管理
	LPDIRECT3D9 direct3d9;	            // 環境を設定するためのインターフェース
	D3DPRESENT_PARAMETERS d3d_pp = {};  // グラフィックス設定用 


	// ウィンドウモード
	LPDIRECT3DDEVICE9 InitD3D(HWND hWnd) {// デバイス

		// LPDIRECT3D9は生成した後ほとんど使用しない
		direct3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		// LPDIRECT3D9のnullチェック
		if (direct3d9 == NULL) {

			MessageBox(0, "IDirect3D9の作成に失敗しました", NULL, MB_OK);
		}

		// パーセントパラメーターズのサイズを0にする
		ZeroMemory(&d3d_pp, sizeof(D3DPRESENT_PARAMETERS));

		/* 描画設定 */
		
		// パラメーターズは全部設定
		d3d_pp.BackBufferWidth = 1920;                         // 横の解像度
		d3d_pp.BackBufferHeight = 1080;						   // 縦の解像度
		d3d_pp.BackBufferFormat = D3DFMT_X8R8G8B8;             // ディスプレイモード
		d3d_pp.BackBufferCount = 1;							   // バックバッファの数
		d3d_pp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;	   // マルチサンプルの数
		d3d_pp.MultiSampleQuality = 0;						   // マルチサンプルの品質レベル
		d3d_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;			   // フロントバッファとバックバッファの切り替え方法
		d3d_pp.hDeviceWindow = hWnd;					       // 画面を描画するウィンドウハンドル
		d3d_pp.Windowed = TRUE;								   // スクリーンモード
		d3d_pp.EnableAutoDepthStencil = TRUE;				   // 深度ステンシルバッファがあるかどうか
		d3d_pp.AutoDepthStencilFormat = D3DFMT_D24S8;		   // ステンシルバッファのフォーマット
		d3d_pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;    // バックバッファからフロントバッファへ転送時のオプション
		d3d_pp.FullScreen_RefreshRateInHz = 0;				   // フルスクリーンでのリフレッシュレート
		d3d_pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // スワップエフェクトの書き換えタイミング

		// デバイスの作成
		direct3d9->CreateDevice(
			D3DADAPTER_DEFAULT,                  // ディスプレイアダプターの種類
			D3DDEVTYPE_HAL,                      // デバイスの種類を設定
			hWnd,								 // デバイスが割り当てられるウィンドウハンドル
			D3DCREATE_HARDWARE_VERTEXPROCESSING, // デバイス制御の組み合わせ
			&d3d_pp,							 // デバイスを設定するためのD3DPRESENT_PARAMETERS構造体
			&d3d_device9						 // LPDIRECT3DDEVICE9のポインタのアドレスに格納する
		);

		// D3Dデバイスのnullチェック
		if (d3d_device9 == NULL) {

			MessageBox(0, "デバイスの生成に失敗しました。", NULL, MB_OK);
			return NULL;// 0ではなくNULLを返す
		}

		// 正常終了
		return d3d_device9;

		/* MEMO
		デバイスの作成に失敗した場合
		PCの端末がDirectXに対応していない場合がある
		*/
	}


	LPDIRECT3DDEVICE9 InitD3DFullScreenMode(HWND h_wnd) {

		// LPDIRECT3D9は生成した後ほとんど使用しない
		direct3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		// LPDIRECT3D9のnullチェック
		if (direct3d9 == NULL) {

			MessageBox(0, "IDirect3D9の作成に失敗しました", NULL, MB_OK);
		}

		ZeroMemory(&d3d_pp, sizeof(D3DPRESENT_PARAMETERS));
		d3d_pp.BackBufferWidth = 1920;
		d3d_pp.BackBufferHeight = 1080;
		d3d_pp.BackBufferFormat = D3DFMT_X8R8G8B8;// 32bit color
		d3d_pp.BackBufferCount = 1;
		d3d_pp.Windowed = FALSE;
		d3d_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3d_pp.EnableAutoDepthStencil = TRUE;
		d3d_pp.FullScreen_RefreshRateInHz = 75;// リフレッシュレート
		d3d_pp.AutoDepthStencilFormat = D3DFMT_D16;// 16Bit Zバッファ作成
		
		direct3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			h_wnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3d_pp,
			&d3d_device9
		);

		// D3Dデバイスのnullチェック
		if (d3d_device9 == NULL) {

			MessageBox(0, "デバイスの生成に失敗しました。", NULL, MB_OK);
			return NULL;// 0ではなくNULLを返す
		}

		// 正常終了
		return d3d_device9;
	}


	// 解像度の変更(今は起動していないので注意)
	void BackBufferReSize(const int&size_x, const int&size_y) {

		d3d_pp.BackBufferWidth = size_x;
		d3d_pp.BackBufferHeight = size_y;

		// リセットメソッド(デバイスの設定を変更する)
		d3d_device9->Reset(&d3d_pp);
		// テクスチャZバッファなど新しいメソッドに作り替えられる
	}


	bool DrawStart()
	{
		// シーンのクリア
		d3d_device9->Clear(
			0,	  // D3DRECT*の矩形の数
			NULL, // ビューポート全体をクリア
		          // Zバッファとステンシルをクリア 
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			NULL, // クリアする色情報(背景色)
			1.0f, // 深度バッファで使用(未使用なら0,f)
			0     // ステンシルバッファで使用する値(未使用なら0)
		);

		// シーン描画を開始する
		if (D3D_OK == d3d_device9->BeginScene())
		{
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


	// D3D9の解放
	void Release() {

		// 生成した時と逆の順番で解放
		d3d_device9->Release();
		direct3d9->Release();
	}


	// 描画領域の設定
	void InitViewPort(DWORD x, DWORD y, D3DVIEWPORT9 &d3d_viewport9) {

		d3d_viewport9.X = x;  // X座標
		d3d_viewport9.Y = y;  // Y座標
		d3d_viewport9.Width;  // 幅
		d3d_viewport9.Height; // 高さ
		d3d_viewport9.MinZ;	  // Z深度 : 最小
		d3d_viewport9.MaxZ;	  // Z深度 : 最大
	}

	// デバイスのゲッター
	LPDIRECT3DDEVICE9 GetLpDirect3DDevice9() {
		return d3d_device9;
	}
}
