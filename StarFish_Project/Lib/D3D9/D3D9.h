#pragma once
#include"../Window/Window.h"



// ==================================
/**
* @file D3D9.h
* @brief DirectX9Graphicsファイル
* @author maekawa
* @2019/06/11
*/
// ==================================


namespace D3D9 {
	

	/**
	* @brief D3D9の初期化
	* @param[in] (width_size) 横のバックバッファサイズ
	* @param[in] (height_size) 縦のバックバッファサイズ
	* @param[in] (windowed) ウィンドウモード
	* @param[in] (back_buffer_count) バックバッファの数
	* @return bool 成功すればtrue,失敗すればfalseを返す
	*/
	bool Init(
		UINT width_size = 1920,
		UINT height_size = 1080,
		BOOL windowed = TRUE,
		UINT back_buffer_count = 1
	);
	

	/** 
	* @brief スクリーンモードの変更
	* @param[in] is_screen_mode スクリーンモードはtrue,フルスクリーンモードはfalse
	*/
	void SetScreenMode(BOOL is_screen_mode);

	
	/**
	* @brief 解像度の変更
	* @param[in] width_size 横のバックバッファサイズ
	* @param[in] height_size 縦のバックバッファサイズ
	*/
	void BackBufferReSize(const int&width_size, const int&height_size);


	/**
	* brief ビューポートの設定
	* @param[in] x 位置X
	* @param[in] y 位置Y
	* @param[in] width ビューポートサイズ横
	* @param[in] height ビューポートサイズ縦
	* @param[in] min_z Z深度最小
	* @param[in] max_z Z深度最大
	*/
	void SetUpViewPort(
		DWORD x,
		DWORD y,
		DWORD width,
		DWORD height,
		FLOAT min_z = 0.f,
		FLOAT max_z = 1.f);


	/**
	* brief 描画領域を伝える
	* @param[in] view_port D3DVIEWPORT9のポインタ
	*/
	void SetViewPort(D3DVIEWPORT9 view_port);


	/**
	* brief 現在DirectXに設定されているビューポートパラメータを受け取る
	* @param[out] d3d_view_port9 デバイスに現在設定されているビューポートパラメータを取得
	* @return bool パラメータの取得に成功すればtrue,失敗すればfalseを返します
	*/
	bool GetViewPort(D3DVIEWPORT9 *d3d_view_port9);


	/**
	* @brief SetSamplerStateをミラーに変更する 
	*/
	void SamplerStateMirror();


	/**
	* @brief SetSamplerStateをクランプに変更する
	*/
	void SamplerStateClamp();


	/**
	* @brief SetSamplerStateをワープに変更する
	*/
	void SamplerStateWrap();


	/**
	* @brief SetSamplerStateをボーダーカラーに変更する
	*/
	void SamplerStateBorderColor();


	/**
	* @brief デバイスのゲッター
	* @return LPDIRECT3DDEVICE9を返す
	*/
	LPDIRECT3DDEVICE9 GetLpDirect3DDevice9();


	/**
	* @brief 描画の開始
	* @return bool 描画に成功すればtrue,失敗すればfalseを返す
	*/
	bool DrawStart();


	/**
	* @brief 描画の終了
	*/
	void DrawEnd();

	
	/**
	* @brief グラフィックスの解放
	*/
	void Release();
}